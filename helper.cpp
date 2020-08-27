#include "helper.h"

Vec2 polar2vec(const PolarVec& p) {
    float s = sin(p.theta);
    float c = cos(p.theta);
    return (Vec2) {
            .x = p.r * c,
            .y = p.r * s,
    };
}

XYTheta RTOmega2XYTheta(const RTOmega& p) {
    float s = sin(p.v.theta);
    float c = cos(p.v.theta);
    return (XYTheta) {
            .x = p.v.r * c,
            .y = p.v.r * s,
            .theta = p.a,
    };
}

RTOmega XYTheta2RTOmega(const XYTheta& p) {
    return (RTOmega) {
            .v.theta = atan2(p.y,p.x),
            .v.r = sqrt(p.x*p.x + p.y*p.y),
            .a = p.theta,
    };
}

PolarVec polar_mul(const float& k, const PolarVec& p) {
    return (PolarVec) {
            .r = k * p.r,
            .theta = p.theta,
    };
}

Vec2 addv2(const Vec2& u, const Vec2& v) {
    return (Vec2) {
            .x = u.x + v.x,
            .y = u.y + v.y,
    };
}

XYTheta Vec2toXYTheta(const Vec2& v) {
    return (XYTheta) {
            .x = v.x,
            .y = v.y,
            .theta = 0,
    };
}

XYTheta sub_xyt(const XYTheta& a, const XYTheta& b) {
    return (XYTheta){
        .x = a.x - b.x,
        .y = a.y - b.y,
        .theta = a.theta - b.theta,
    };
}

XYTheta add_xyt(const XYTheta& a, const XYTheta& b) {
    return (XYTheta){
        .x = a.x + b.x,
        .y = a.y + b.y,
        .theta = a.theta + b.theta,
    };
}

XYTheta mul_xyt(const XYTheta& a, const XYTheta& b) {
    return (XYTheta){
        .x = a.x * b.x,
        .y = a.y * b.y,
        .theta = a.theta * b.theta,
    };
}
