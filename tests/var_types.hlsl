//shared const float4 global_var_2 : register(c2);
//error X3000: syntax error: unexpected integer constant
//                                 : register(3);
//  error X3091: packoffset is only allowed in a constant buffer
//                                 : packoffset(c0.x);

float ann_var_0 <float min=1;>;

float4 ann_var_1 <float min=1; float max = 1; float4 blah=float4(0, 0, 0, 0);>;

float4x4 world;

uniform const float global_var_1 : register(c0);

const float global_var_1_2 : register(c1);

uniform float global_var_1_3;

shared const float4 global_var_2 : register(c2);

shared const float4x4 global_var_3 : register(ps, c14)
                                   : register(vs, c3);

float4 ann_var_2 <const float min=1; float max = 1; float4 blah={0, 0, 0, 0};>;

float4x4 ann_var_3 <row_major float2x2 min={0, 0, 0, 0}; string blah2 = "Some string \"literal\"";>;

float4 in_normal : NORMAL; // semantics are syntactically valid here but will not appear in the input signature! (even when used in by entry point)

cbuffer const_buf_1 {
    float4 some_const_thing_1;// = float4(1,0,0,1); TODO default assignments
    float4x4 some_const_thing_2;
    float4 some_const_thing_0 : TEXCOORD0; // semantics are syntactically valid on cbuffers is seems but will not appear in the input signature!
};

cbuffer const_buf_2 : register(c10) {
    // : register(xx) and packoffset(xx) cannot be mixed in the same cbuffer it seems
    float4 some_const_thing_3 : packoffset(c0);
    float some_const_thing_4 : packoffset(c1.x);
    float some_const_thing_5 : packoffset(c1.g);
    float2 some_const_thing_6 : packoffset(c1.z); // packoffset(XY.x) specifies the first element to fill (so .zw in this case, .w is invalid)
};

cbuffer const_buf_3 : register(vs, c11) : register(ps, c11) {
    // : register(xx) and packoffset(xx) cannot be mixed in the same cbuffer it seems
    float4 some_const_thing_7 : register(c0);
    const float some_const_thing_8 : register(c1); // register doesn't support c1.x style
    uniform const float some_const_thing_9 : register(c1);
    shared float2 some_const_thing_10 : register(c1);
};

// uniform <- not valid syntax
struct VSInput {
    float3 position : POSITION;
    float4 colour : TEXCOORD0;
    float2 uv : TEXCOORD1;
};

struct VSInput2 {
    float3 position : POSITION; // it is syntactically valid to have semantics on some members, not all
    float4 colour;
    float2 uv; // = [initial value]  is not valid in this case
};

// following is valid. Note swap of const<->uniform
const uniform 
struct TestStruct {
    row_major float4x4 mem11;
    centroid float4 mem12;
    float4 mem13;
    // static float4 mem14; // Wat!?
} const_input_0;

//float4 TestStruct::mem14; // Wat!?

// following is valid. Note swap of const<->uniform
const uniform 
struct { // anonymous struct
    float4 mem1;
    float4 mem2;
    float4 mem3;
    float4 mem4;
} const_input_1 : register(c30); // anonymous is only when declaring 

// function prototypes
float local_max_0();
float local_max(float abc, float bcd);
const float local_min(float a, float b);
float4 main_ps() : SV_Target0;
float4 main_vs(float3 in_pos : POSITION, float4 in_tc : TEXCOORD1) : SV_POSITION;


float4 main_vs(float4 in_pos : POSITION, float4 in_tc : TEXCOORD1) : SV_POSITION {
    ++in_pos;
    return float4(in_pos+in_normal, 1)
    + some_const_thing_0
    + some_const_thing_1
    + in_tc;
}

float4 main_ps() : SV_Target0 {
    return float4(1, 0, 0, 1);
}

float local_min(float a, float b) {
    return a < b ? a : b;
}
