///////////////////////////////////////////////////////////////////////
// color.hlsl
// HLSL : High Level Shader Language
//                    -> ���ſ��� Assembler
//                    -> C �� �����ߴ�.
//  *���Ǵ� function �̸��� ���� �̸����� Shader �� �������ش�.
//
//  PNG -> ������ �ִ� �׸�����
//  BMP -> ������ ���� �׸�����
//
//  �̹����� ������ UV ��ǥ�� �ִµ�. �ؽ��ĸ� ������ UV ��ǥ�� ����Ѵ�.
//
//
///////////////////////////////////////////////////////////////////////

// ������ ���� ���� �����͸� �����ִ� �����̴�.
struct VertexInput
{
    float4 position : POSITION0; // Sementics Name [n] �� �ø�ƽ�� �ѹ�
    float2 uv       : TEXCOORD0; // Texture cooredinate
};

struct PixelInput
{
    float4 position : SV_POSITION0; // System Value
    float2 uv       : TEXCOORD0;
};

// ��� ���۸� ���� ������ �ϴ� ���̴��̴�.

cbuffer Transformbuffer : register(b0) // 0~13 ���Կ� ��� (4096 * 16byte ���� 16���)
{
    // matrix �� (float) 4x4 �� ���·� �̷�����ִ�.
    // �׸��� ũ�⸦ �����ϱ� ���ؼ��� scale
    // ��ġ�� �̵��ϱ� ���ؼ��� trans
    // ȸ���ϱ� ���ؼ��� rotate
    // �̿Ͱ��� ���� ���ϰ� ����ϱ� ���� matrix �� ����Ѵ�.
    // ����ȭ�� ��ǥ�� ������ �ִ� DX ���� ���� ȭ�鿡�� �ʿ��� ���� ���ϱ����� matrix �� �����ִ°��̴�.
    
    matrix world;   // ���ڽſ� ���� ������
    matrix view;    // �� (ī�޶�)�� ���� ����
    matrix proj;    // Projecter ȭ���� ���⶧ 2D �� �����翵
};

cbuffer ColorBuffer : register(b1)  // 4byte �� ����� ��������Ѵ�
{
    float4 textColor;   // �ٲ� Į��
    int    path;        // switch �� ������ Tag
    float  time;
    float  dummy1;
    float  dummy2;
}

// 4 / 25 multi shader

Texture2D sourc_texture1[2] : register(t0); // Texture �ڿ� �̶�� ��
Texture2D sourc_texture2 : register(t1); // �Ǵٸ� Texture �� ������ ����Ѵ�
// Texture �� �ϳ��� ���̴��� 128�� ���� ������ �ִ�.

SamplerState samp : register(s0); // Ȯ�� ��� (Sampling) �� �Ҷ� ����Ѵ�.
// SampleState �� 0~15 ���� ���� �� �ִ�.

//////////////////////////////////////////////////////
// VertexShader ���α׷�
//
//////////////////////////////////////////////////////

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, world); // ���� ��ȯ
    output.position = mul(output.position, view); // �� ��ȯ
    output.position = mul(output.position, proj); // �������� ��ȯ
    output.uv       = input.uv;
    
    return output;
}

//////////////////////////////////////////////////////
// PixelShader ���α׷�
//
//////////////////////////////////////////////////////

static const float Weights[13] =
{
    0.0561f, 0.1353f, 0.278f, 0.4868f, 0.7261f, 0.9231f,
    1.0f,
    0.9231f, 0.7261f, 0.4868f, 0.278f, 0.1353f, 0.0561f
};

float4 PS(PixelInput input) : SV_Target // ���� ���õ� ���η���Ÿ�� �� ����϶�� �˷��ش�.
{
    float4 color = sourc_texture1[0].Sample(samp, input.uv); // Texture �� ����� ������ color �� ���Եȴ�.
    float4 color2 = sourc_texture1[1].Sample(samp, input.uv); // Texture �� ����� ������ color �� ���Եȴ�.
    float4 returnColor = color;
    float4 alpha = float4(color.rgb, 0); // ����
    float4 alpha2 = color;  // ǥ�ػ�
    
    [forcecase]
    
    switch (path)
    {
        //case 0:
        //    break;
        case 1:
            returnColor = float4(textColor.r, textColor.g, textColor.b, color.a);
            break;
        case 2:
            if (color.a <= 0.0f)
                discard;
            returnColor = lerp(textColor, alpha, time); // ���� ����, ������ alpha ~ 0 
            break;
        case 3:
            if (input.position.y < dummy1)
                discard;
            if (input.position.y > dummy2)
                discard;
            break;
        case 4:
            if (color.a <= 0.3f)
                discard;
            returnColor = float4(textColor.r, textColor.g, textColor.b, textColor.a);
            break;
        case 5:
            alpha = float4(textColor.rgb, alpha2.a);
        
            returnColor = lerp(alpha, alpha2, time);
            break;
        case 6:
            alpha = float4(color.rgba);
            alpha2 = float4(textColor.rgb, alpha2.a);
        
            returnColor = lerp(alpha, alpha2, time);
        
            break;
        case 7:
            if (color.a <= 0.1f)
                discard;
            returnColor = float4(color.r, color.g, color.b, textColor.a);
            break;
        case 9:
            returnColor = float4(color.r * textColor.r, color.g * textColor.g, color.b * textColor.b, color.a);
            break;
		case 10:
			returnColor = float4(color * 0.5f + color2 * 0.5f);
			break;
        case 11:
            if (color.r >= 98.0f / 255.0f && color.g >= 88.0f / 255.0f && color.b >= 106.0f / 255.0f)
                discard;
            break;
        case 12:
            float2 uv = input.uv;
            float u = 2.0f / 1980.0f;

            float sum = 0;
            float4 color4 = 0;

            for (int i = -6; i <= 6; i++)
            {
                float2 temp = uv + float2(u * (float) i, 0.0f);
                color4 += sourc_texture1[0].Sample(samp, temp) * Weights[6 + i];

                sum += Weights[6 + i];
            }

            color4 /= sum;
            returnColor = color4;
            break;
    }
    
    if (returnColor.r == 1.0f && returnColor.g == 0.0f && returnColor.b == 1.0f)
        discard;
    
    return returnColor;
}