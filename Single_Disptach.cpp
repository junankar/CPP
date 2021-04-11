#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class RaceCar
{
    public:
        RaceCar() = default;
        ~RaceCar() = default;
};

class FormulaOneCar: public RaceCar
{
    public:
        FormulaOneCar() = default;
        ~FormulaOneCar() = default;
};

class GasStation
{
    public:
        GasStation() = default;
        ~GasStation() = default;

        void FillGas(RaceCar* car)
        {
            cout << "Selecting Octane 87 fuel" << endl;
        }

        void FillGas(FormulaOneCar* car)
        {
            cout << "Selecting Octane 95 fuel" << endl;
        }        
};

int main()
{
    vector< shared_ptr<RaceCar> > raceCars {
        shared_ptr<RaceCar>(new RaceCar()),
        shared_ptr<RaceCar>(new FormulaOneCar())
        };

    GasStation gasStation;
    for(auto raceCar : raceCars)
    {
        gasStation.FillGas(raceCar.get());
    }
}