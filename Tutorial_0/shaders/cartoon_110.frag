#version 110

uniform vec4 color0;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

varying vec3 normal;

void main()
{
    float intensity = dot(vec3(gl_LightSource[0].position), normal);

    if (intensity > 0.95)
    {
        gl_FragColor = color0;
    }
    else if (intensity > 0.5)
    {
        gl_FragColor = color1;
    }
    else if (intensity > 0.25)
    {
        gl_FragColor = color2;
    }
    else
    {
        gl_FragColor = color3;
    }
}