/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#pragma once // is valid! yay \o/

register(vs, 9) register(ps, 10) 
cbuffer ViewportConstants {
    float4x4 view;
    float4x4 viewInverse;
    float4x4 viewInverseTranspose;
    float4x4 projection;
    float4x4 projectionInverse;
    float4x4 viewProjection;
    float4x4 viewProjectionInverse;
    float4 viewportSize;
};
