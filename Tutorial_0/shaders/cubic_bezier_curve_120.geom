#version 120

#extension GL_EXT_geometry_shader4 : enable

uniform int segmentCount;

void main()
{
    float delta = 1.0 / float(segmentCount);

    vec4 vector;

    for (int i = 0; i <= segmentCount; ++i)
    {
        float t = delta * float(i);
        float t_squared = t * t;
        float one_minus_t = 1.0 - t;
        float one_minus_t_squared = one_minus_t * one_minus_t;

        vector = gl_PositionIn[0] * one_minus_t_squared * one_minus_t +
                 gl_PositionIn[1] * 3.0 * t * one_minus_t_squared +
                 gl_PositionIn[2] * 3.0 * t_squared * one_minus_t +
                 gl_PositionIn[3] * t_squared * t;

        gl_Position = vector;

        EmitVertex();
    }

    EndPrimitive();
}