varying vec2 texCoord;

uniform sampler2D tex0;
uniform mat4x4 colorMatrix;
uniform sampler2D tex1;

uniform sampler2D tex2;
uniform mat4x4 light0;
varying vec3 normal;

varying vec3 lightVec;
void main(){
	float llv = length(lightVec);
	float atscale = light0[0][3];
	float diffuseAtt = 0.5/(1 + llv*llv*0.1) +0.5/(llv*0.05 +1); 
	vec4 color = texture2D(tex0,texCoord);
	vec4 color2 = texture2D(tex1,texCoord);
	vec4 color3 = texture2D(tex2,texCoord);
	// color = vec4(1,0,1,1);
	
	gl_FragColor	 =colorMatrix[2] + (color + color2 + color3)*light0[0]*diffuseAtt;
	
}
