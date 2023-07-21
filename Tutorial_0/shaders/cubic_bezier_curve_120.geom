#version 120

#extension GL_EXT_geometry_shader4 : enable

uniform int segmentCount;

void main()
{
    vec4 pointOnCurve;

    for (int i = 0; i <= segmentCount; ++i)
    {
        float t = 1.0 / float(segmentCount) * float(i);

        // Bezier curve substituted formula.
        // P0, P1, P2 and P3 are control points.
        // P(t) = (1-t)^3 * P0 + 3*t*(1-t)^2 * P1 + 3*t^2*(1-t) * P2 + t^2 * P3

        pointOnCurve = pow((1 - t), 3.0) * gl_PositionIn[0] +
                 3 * t * (pow((1 - t), 2.0)) * gl_PositionIn[1] +
                 3 * pow(t, 2.0) * (1 - t) * gl_PositionIn[2] +
                 pow(t, 3.0) * gl_PositionIn[3];

        gl_Position = pointOnCurve;

        EmitVertex();
    }

    EndPrimitive();
}