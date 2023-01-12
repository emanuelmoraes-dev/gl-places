#ifndef _PL_DELTA_HH_INCLUDED_
#define _PL_DELTA_HH_INCLUDED_

namespace upl {
    class DeltaF {
    private:
        float _value;
        float _diff;
        bool _initialized;
    public:
        DeltaF();
        DeltaF(float value);
        void reset();
        void tick(float value);
        float delta() const;
    };
}

#endif
