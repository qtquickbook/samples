uniform highp float rangeLow;
uniform highp float rangeHigh;
uniform sampler2D source; // this item
uniform lowp float qt_Opacity; // inherited opacity of this item
varying highp vec2 qt_TexCoord0;
void main() {
    lowp vec4 p = texture2D(source, qt_TexCoord0);
    lowp float a = (p.r - rangeLow) / (rangeHigh - rangeLow);
    lowp float v = a * 1023.0;
    lowp float b = v < 256.0 ? v :
                   v < 512.0 ? 255.0 :
                   v < 768.0 ? 255.0 - (v-512.0) : 0.0;
    lowp float g = v < 256.0 ? 0.0 :
                   v < 512.0 ? v - 256.0 :
                   v < 768.0 ? 255.0 : 255.0 - (v-768.0);
    lowp float r = v < 512.0 ? 0.0 :
                   v < 768.0 ? v - 512.0 : 255.0;
    gl_FragColor = vec4(r/255.0, g/255.0, b/255.0, 1.0) * qt_Opacity;
}
