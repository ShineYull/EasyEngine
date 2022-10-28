#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    //FragColor = texture(ourTexture1, TexCoord) * ourColor;
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}