varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
// Uniform defined for our use
uniform vec2 loc;

void main()
{
	// Get the pixel value at the current location from the built-in Cocos2d uniform "CC_Texture0"
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	
	float grey = (texColor.r + texColor.g + texColor.b) / 3;
	
	gl_FragColor = v_fragmentColor * vec4(grey, grey, grey, texColor.a);
}