#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require
#pragma STDGL invariant(all)
#pragma optimize(on)
#pragma debug(on)
#include "/common.glsl" //! #include "../../../templates/common.glsl"
#include "/common.frag.glsl" //! #include "../../../templates/common.frag.glsl"


uniform vec3 iResolution = vec3(1024, 1024, 1); // viewport resolution (in pixels)
uniform float iTime = 1.5; // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;


#define Max_Steps 64
#define Max_Dist  100.
#define Min_Surf_Dist 0.01


vec3 palette(float d)
{
	return mix(vec3(0.2,0.7,0.9),vec3(1.,0.,1.),d);
}

vec2 rotate(vec2 p,float a)
{
	float c = cos(a);
    float s = sin(a);
    return p*mat2(c,s,-s,c);
}

float map(vec3 p)
{
    for( int i = 0; i<8; ++i)
    {
        float t = iTime*0.2;
        p.xz =rotate(p.xz,t);
        p.xy =rotate(p.xy,t*1.89);
        p.xz = abs(p.xz);
        p.xz-=.5;
	}
	return dot(sign(p),p)/5.;
}

// ro: ray origin
// rd: ray direction
vec4 rm (vec3 ro, vec3 rd)
{
    float _min_distance = 0.0f;
    float _cumulant  = 0.0f;
    vec3 _color = vec3(0.0f);
    vec3 _current_position = vec3(0.0f);

    for(int _index = 0; _index < Max_Steps; ++_index)
    {
        // arrive at new point
		_current_position = ro + rd * _cumulant;
        // current min distance
        _min_distance = map(_current_position) * 0.5f; 
        // when condition true, over
        // < Min_Surf_Dist means interact, 
        // > Max_Dist means never interact
        if(_min_distance < Min_Surf_Dist || _min_distance > Max_Dist)
        {
            break;
        }
        // total distance moved
        _cumulant += _min_distance;
        // color
        _color += palette( length(_current_position) * .1) / (400. * (_min_distance) );
    }
    return vec4(_color, 1. / (_min_distance * 100.));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord-(iResolution.xy/2.))/iResolution.x; // screen uv
	vec3 ro = vec3(0.,0.,-50.); // ray origin (camera/eye position)
    ro.xz = rotate(ro.xz,iTime); // 
    
    vec3 cf = normalize(-ro);
    vec3 cs = normalize(cross(cf,vec3(0.,1.,0.)));
    vec3 cu = normalize(cross(cf,cs));
    vec3 uuv = ro+cf*3. + uv.x*cs + uv.y*cu;

    vec3 rd = normalize(uuv-ro); // ray direction
    vec4 col = rm(ro,rd); // if marched, return the suf color, if not marched return the evn color
    
    fragColor = col;
}


//// 获取当前点和场景中是所有物体相交的最小距离
//float GetDist(vec3 p)
//{
//    vec4 s = vec4(0,1,6,1);// 球的位置(s.xyz)和半径（s.w）
//    float sphereDist = length(p-s.xyz)-s.w;// P点到球面的距离
//    float planeDist  = p.y;// P点到平面的距离，平面是xz平面，高度y = 0；
//    
//    float d = min(sphereDist,planeDist);
//    return d;
//}
//
//float RayMarch(vec3 ro, vec3 rd)
//{
//    float d0 = 0.;
//    for(int i = 0; i < Max_Steps; i++)
//    {
//        vec3 p = ro + rd*d0;
//        float ds = GetDist(p);
//        d0+=ds;
//        if(d0>Max_Dist || ds < Min_Surf_Dist) 
//            break;           
//    }
//                     
//    return d0;     
//}
//
//// 顶点的法线
//vec3 GetNormal(vec3 p)
//{
//    float d = GetDist(p);
//    vec2 e = vec2(0.01, 0);
//    vec3 n = d - vec3(GetDist(p-e.xyy), GetDist(p-e.yxy), GetDist(p-e.yyx));
//    return normalize(n);
//}
//
//// 计算灯光，点光源
//float calcLight(vec3 p)
//{
//    vec3 lightPos = vec3(0,5,6);
//    lightPos.xz += vec2(sin(iTime), cos(iTime)) * 2.0;
//    vec3 l = normalize(lightPos-p);
//    vec3 n = GetNormal(p);
//    
//    float dif = clamp(dot(n,l), 0., 1.);
//    
//    float d = RayMarch(p + n*Min_Surf_Dist*2.0,l);
//
//    if(d < length(lightPos-p)) 
//    {
//        dif*=0.1;
//    }
//
//    return dif;
//}
//
//void mainImage( out vec4 fragColor, in vec2 fragCoord )
//{
//    vec2 uv = (fragCoord- 0.5 * iResolution.xy) / iResolution.y;
//    vec3 col = vec3(0);
//    
//    vec3 ro = vec3(0, 1, 0);
//    vec3 rd = normalize(vec3(uv.x,uv.y,1.));
//    
//    float d = RayMarch(ro, rd);
//    vec3 _current_position = ro + rd * d;
//    float _diffuse = calcLight(_current_position);
//    
//    col = vec3(_diffuse);
//    fragColor = vec4(col,1.0);
//}

out vec4 out_color;

void main()
{
	out_color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    mainImage(out_color, gl_FragCoord.xy);
}