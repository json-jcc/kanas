#version 460 core
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)

// warn, disable
//#extension all : disable

// require, enable, warn, disable, 
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require


uniform vec3 iResolution = vec3(1024, 1024, 1); // viewport resolution (in pixels)
uniform float iTime = 1.5; // shader playback time (in seconds)
//uniform float     iTimeDelta;            // render time (in seconds)
//uniform int       iFrame;                // shader playback frame
//uniform float     iChannelTime[4];       // channel playback time (in seconds)
//uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
//uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
//uniform vec4      iDate;                 // (year, month, day, time in seconds)
//uniform float     iSampleRate;

#define MAXDIST 20.
#define GIFLENGTH 1.570795

struct Ray {
	vec3 ro;
    vec3 rd;
};

void pR(inout vec2 p, float a) 
{
	p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}

float length6( vec3 p )
{
	p = p*p*p; p = p*p;
	return pow( p.x + p.y + p.z, 1.0/6.0 );
}

float fractal(vec3 p)
{
   	float len = length(p);
    p=p.yxz;

    float scale = 1.25;
    const int iterations = 28;
    float a = iTime;
	float l = 0.;
    
    vec2 rotationAnimAmp = vec2(0.05,0.04);
	vec2 rotationPhase = vec2(.45 + sin(iTime*4. + len*0.4) * 0.025,0.15 + cos(-0.2+iTime*4. + len*0.2) * 0.05);
    // uncomment this to find good spots with the mouse :)
    //m = iMouse.xy / iResolution.xy;
    vec3 juliaOffset = vec3(-3.,-1.15,-.5);
    pR(p.xy,.5+sin(-0.25+iTime*4.)*0.1);
    for (int i=0; i<iterations; i++) {
		p = abs(p);
        // scale and offset the position
		p = p*scale + juliaOffset;
        // Rotate the position
        pR(p.xz,rotationPhase.x*3.14 + cos(iTime*4. + len)*rotationAnimAmp.y);
		pR(p.yz,rotationPhase.y*3.14 + sin(iTime*4. + len)*rotationAnimAmp.x);		
        l=length6(p);
	}
	return l*pow(scale, -float(iterations))-.25;
}

vec2 map(vec3 pos) {
    float l = length(pos);
    float dist = fractal(pos);
    return vec2(dist, 0.);
}

vec2 march(Ray ray) 
{
    const int steps = 30; // 最大步数，同时超出MAXDIST终止
    const float prec = 0.001; // 最小距离，小于这个距离判相交
    vec2 res = vec2(0.);
    for (int i = 0; i < steps; i++) 
    {        
        vec2 s = map(ray.ro + ray.rd * res.x);
        if (res.x > MAXDIST || s.x < prec)
        {
        	break;    
        }
        res.x += s.x;
        res.y = s.y;
    }
   
    return res;
}

vec3 calcNormal(vec3 pos) 
{
	const vec3 eps = vec3(0.005, 0.0, 0.0);
    return normalize(
        vec3(
        map(pos + eps).x - map(pos - eps).x, 
        map(pos + eps.yxz).x - map(pos - eps.yxz).x, 
        map(pos + eps.yzx).x - map(pos - eps.yzx).x
        ) 
    );
}

float calcAO( in vec3 pos, in vec3 nor )
{
    float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.2*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).x;
        occ += -(dd-hr)*sca;
        sca *= .95;
    }
    return clamp( 1.0 - 2.0*occ, 0.0, 1.0 );
}

vec4 render(Ray ray) 
{
    vec3 col = vec3(0.);
	vec2 res = march(ray);
   
    if (res.x > MAXDIST) 
    {
        return vec4(col, MAXDIST);
    }
    
    vec3 p = ray.ro+res.x*ray.rd;
    vec3 normal = calcNormal(p);
    vec3 pos = p;
    ray.ro = pos;
    // color with ambient occlusion
   	col = vec3(pow(calcAO(p, normal), 3.2))*0.5;
   
    col = mix(col, vec3(0.), clamp(res.x/MAXDIST, 0., 1.));
   	return vec4(col, res.x);
}

mat3 camera(in vec3 ro, in vec3 rd, float rot) 
{
	vec3 forward = normalize(rd - ro);
    vec3 worldUp = vec3(sin(rot), cos(rot), 0.0);
    vec3 x = normalize(cross(forward, worldUp));
    vec3 y = normalize(cross(x, forward));
    return mat3(x, y, forward);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // screen uv
	vec2 _uv = fragCoord.xy / iResolution.xy;
    _uv = _uv * 2.0 - 1.0;
    _uv.x *= iResolution.x / iResolution.y;
    
    // camera mat
    vec3 _cam_pos = vec3(9.0f, 6.5f, 12.0f);
    vec3 _cam_dir = _cam_pos + vec3(-0.85f, -0.5f, -1.0f);
    mat3 _cam = camera(_cam_pos, _cam_dir, 0.0f);
    
    // initial ray dir
    vec3 _ray_dir = _cam * normalize(vec3(_uv, 1.0f + sin(iTime * 4.0f) * 0.05f));
    
    Ray _ray;
    _ray.ro = _cam_pos;
    _ray.rd = _ray_dir;
    vec4 _color = render(_ray);

    _color.xyz = pow(_color.xyz, vec3(0.6f));
	fragColor = vec4(_color.xyz, clamp(1.0f - _color.w / MAXDIST, 0.0f, 1.0f));
}

out vec4 out_color;

void main()
{
	//out_color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    mainImage(out_color, gl_FragCoord.xy);
}