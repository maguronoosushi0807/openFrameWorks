// blurHorizontal.frag
#version 120
uniform sampler2D tex0; // 入力テクスチャ
uniform float blurAmount; // ブラー量
uniform vec2 resolution; // 画面の解像度

void main() {
    vec2 texCoord = gl_TexCoord[0].st;
    vec2 texOffset = vec2(blurAmount / resolution.x, 0.0); // 横方向のオフセット
    vec4 color = vec4(0.0);

    // サンプル（ぼかし半径を5に設定）
    color += texture2D(tex0, texCoord + texOffset * -2.0) * 0.12;
    color += texture2D(tex0, texCoord + texOffset * -1.0) * 0.25;
    color += texture2D(tex0, texCoord) * 0.26;
    color += texture2D(tex0, texCoord + texOffset * 1.0) * 0.25;
    color += texture2D(tex0, texCoord + texOffset * 2.0) * 0.12;

    gl_FragColor = color;
}
