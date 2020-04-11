#ifndef GENCONDITION_H
#define GENCONDITION_H

class GenCondition
{
public:
    virtual ~GenCondition() {}
    virtual bool operator() () = 0;
};

#endif // GENCONDITION_H
