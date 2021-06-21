#pragma once

struct CustomType
{
    int cint;
    bool operator==(const CustomType &r) const
    {
        return cint == r.cint;
    }
    bool operator!=(const CustomType &r) const
    {
        return cint != r.cint;
    }
};
