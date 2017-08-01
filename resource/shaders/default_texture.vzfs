#version 330 core

out vec4 FragColor;

in vec3 Color_vs;
in vec2 TexCoord_vs;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = mix(texture(texture1, TexCoord_vs), texture(texture2, TexCoord_vs), 0.2);
}