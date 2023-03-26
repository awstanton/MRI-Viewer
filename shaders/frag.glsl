#version 330 core

//uniform triangleColor;
//in float Color;
//out vec4 outColor;

// gets texture unit from main function
uniform sampler2D tex0;

// inputs color from vertex shader
in vec2 texCoord;

// output colors in Red - TODO
out vec4 FragColor;

void main()
{
    vec4 texColor = texture(tex0, texCoord);
//    FragColor = vec4(texColor[0], texColor[0], texColor[0], texColor[3]);
    FragColor = vec4(texColor[0], texColor[0], texColor[0], texColor[3]);
//    float val = (Color[0] + Color[1] + Color[2]) / 3;
//    outColor = vec3(val, val, val);
//    outColor = vec3(Color, Color, Color);
//    outColor = vec4(Color, Color, Color, 1.0);
}
