// blurHorizontal.frag
#version 120
uniform sampler2D tex0; // ���̓e�N�X�`��
uniform float blurAmount; // �u���[��
uniform vec2 resolution; // ��ʂ̉𑜓x

void main() {
    vec2 texCoord = gl_TexCoord[0].st;
    vec2 texOffset = vec2(blurAmount / resolution.x, 0.0); // �������̃I�t�Z�b�g
    vec4 color = vec4(0.0);

    // �T���v���i�ڂ������a��5�ɐݒ�j
    color += texture2D(tex0, texCoord + texOffset * -2.0) * 0.12;
    color += texture2D(tex0, texCoord + texOffset * -1.0) * 0.25;
    color += texture2D(tex0, texCoord) * 0.26;
    color += texture2D(tex0, texCoord + texOffset * 1.0) * 0.25;
    color += texture2D(tex0, texCoord + texOffset * 2.0) * 0.12;

    gl_FragColor = color;
}
