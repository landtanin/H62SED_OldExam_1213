#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <conio.h>



//------------------------------------------------------------------------------------------------------

class power_company;

class power_station;

class customer;

class customer_factory;

using namespace std;


//--------------It is important to  first of all, initialize class like this----------------------------


class power_station{

    public:

    // constructor
    power_station(float _max_power_generate = 0., float _cost_eff = 0., bool _status = false)

      :max_power_generate(_max_power_generate),cost_eff(_cost_eff),status(_status){}

    // copy constructor
    power_station(const power_station& ps)

      :max_power_generate(ps.max_power_generate),cost_eff(ps.cost_eff),status(ps.status){}

    /*
    // istream
    power_station(istream& in){

      in>>*this;

    }
    */

    // operator overloading
    power_station& operator=(const power_station& ps){

      if(this==&ps) return(*this);

      max_power_generate = ps.max_power_generate;

      cost_eff = ps.cost_eff;

      status = ps.status;

      return(*this);

    }

    // destructor
    ~power_station(){}

    float get_cost_eff() const{return cost_eff;}

    void set_cost_eff(const float _cost_eff){cost_eff=_cost_eff;}

    float get_max_power_generate() const{return max_power_generate;}

    void set_max_power_generate(const float _max_power_generate){

      max_power_generate = _max_power_generate;

    }

    bool get_status(){return status;} // solution : float get_status(){return status;}

    void set_status(bool _status){status = _status;}


    // friend ostream& operator<<(ostream& out, const power_station& ps); // stream output file

    // friend istream& operator>>(istream& in, power_station& ps); // stream input file


    private:

        float max_power_generate;  // kW

        float cost_eff;            // Pence/kWh

        bool status;               // trure on, false off

}; // class power_station

//------------------------------------------------------------------------------

class power_company{

    public:

    // constructor
    power_company(int _no_stations, int _no_customers, power_station** _stations, customer** _customers){

      no_stations = _no_stations;

      no_customers = _no_customers;

      if(no_stations>10||no_stations<0){ cout<<"\ninvalid input data";exit(0);}

      if(no_customers>100||no_customers<0){ cout<<"\ninvalid input data";exit(0);}

      for(int i=0;i<no_stations;i++) stations[i] = _stations[i]; // 10 power stations

      for(int i=0;i<no_customers;i++) customers[i] = _customers[i]; // 100 customers

    }

    // copy
    power_company(const power_company& pc){

      /*
      if(pc.no_stations<=10) no_stations = pc.no_stations;

      if(pc.no_customers<=100) no_customers = pc.no_customers;

      for(int i = 0;i<no_stations;i++)
      {
          stations[i] = new power_station(*(pc.stations[i]));
      }

      for(int i = 0;i<no_customers;i++)
      {
          customers[i] = new customer_factory(*(pc.customers[i]));
      }
      */ // my code

      *this=pc; // solution

    }

    /*
    // istream
    power_company(istream& in){

      in>>*this;

    }
    */ // my code

    const power_company& operator=(const power_company& pc){

      if(this==&pc) return(*this);

      no_stations = pc.no_stations;

      no_customers = pc.no_customers;

      /*

      delete[] stations; // we not sure about the size of this array so we have to clear in and re-allocate (different from copy constructor)

      stations = new power_station*[no_stations];

      for(int i = 0;i<no_stations;i++){

          stations[i] = new power_station(*(pc.stations[i]))

      }

      */ // my code

      for(int i = 0;i<no_stations;i++) stations[i] = pc.stations[i]; // solution

      /*
      delete[] customers; // we not sure about the size of this array so we have to clear in and re-allocate (different from copy constructor)

      customers = new customer_factory*[no_customers];

      for(int i = 0;i<no_customers;i++){

          customers[i] = new customer_factory(*(pc.customers[i]))

      }
      */ // my code

      for(int i = 0;i<no_customers;i++) customers[i] = pc.customers[i];

      return(*this); // don't forget to return this for the operator=

    }

    // destructor
    ~power_company(){

      // if(stations!=NULL) delete[] stations; // STATIC array of pointer don't need to clear memory

      // if(customers!=NULL) delete[] customers;

    }

    int get_no_stations(){return no_stations;} // get1

    // void set_no_stations(const int _no_stations); // no sets!

    void set_more_power_station(power_station* const ps){

      if(no_stations==10){

        cout<<"\nCannot add any more power station";exit(0);

      }

      stations[no_stations++] = ps; // we can assign ps directly to the array member because
                                         // its an array of pointer, so we can assign pointer to it

    } // look like copy constructor

    void add_customer(customer* const _customer){

      /*
      customer_factory** added_customer = new customer_factory*[no_customers+1];

      if((no_customers+1)<99){

        for(int i = 0;i=<(no_customers+1);i++){

          if(i==(no_customers+1)) added_customer[i] = _customer_factory;

          else added_customer[i] = customers[i];

        }
      }

      customers = added_customer;

      delete[] added_customer;
      */ // my code is follow the basis from OldExam 1415 (dynamic array)

      if(no_customers==100){

        cout<<"\nInvalid input data";exit(0);

      }

      customers[no_customers++]=_customer;

    }

    void delete_customer(customer* const _customer){ // beware! look at the position of const
      /*
      int array_of_delete_factory = 0

      for(int i = 0;i<no_customers;i++){

        if(customers[i]==_customer_factory) array_of_delete_factory = i;

      }

      int skip_array = 0;

      customer_factory** new_customer_list = new customer_factory*[no_customers-1];

      if((no_customers-1)<99){

        for(int i = 0;i<(no_customers-1);i++){

          if(i==array_of_delete_factory) skip_array = 1;

          new_customer_list[i] = customers[i+skip_array];

        }
      }

      customers = new_customer_list;

      delete[] new_customer_list;
      */ // my code is follow the basis of OldExam 1415 (dynamic array)

      for(int i = 0;i<no_customers;i++){

        if(_customer==customers[i]){

          for(int j = i+1;j<no_customers;j++){ // j is a list of customer that shift up by one

            customers[j-1] = customers[j]; // j-1 is the original sequence

          }

          no_customers--;

        }

      }


    }



    // friend ostream& operator<<(ostream& out, const power_company& s); // stream output file

    // friend istream& operator>>(istream& in, power_company& s); // stream input file




    private:

        int no_stations;

        int no_customers;

        power_station* stations[10]; // beware! static array of poiner have only one *

        customer* customers[100]; // static array is what make the solution look so simply


}; // class power_company

//------------------------------------------------------------------------------


class customer{

public:

    // constructor
    customer(power_company* _supplier):supplier(_supplier){

      // tell the power_company to add this customer to their list
      supplier->add_customer(this);

    }

    // copy constructor
    customer(const customer& c):supplier(c.supplier){ // pointer "cf.supplier" copy to "supplier"

      // tell the power_company to add this customer to their list
      supplier->add_customer(this);

    }

    /*
    // istream
    customer_factory(istream& in){

      in>>*this;

    }
    */

    // operator overloading
    virtual const customer& operator=(const customer& c){

      supplier = c.supplier; // ??? where is "this"

    }

    // destructor
    virtual ~customer(){

      supplier->delete_customer(this);

    }

    private:

        power_company* supplier;



};

//------------------------------------------------------------------------------

class customer_factory:public customer{

    public:

    // constructor
    customer_factory(power_company* _supplier, float _max_power_require)

      :customer(_supplier), max_power_require(_max_power_require){ // beware! the constructor of base class must call first

      // tell the power_company to add this customer_factory to their list
      // this is perform by class customer
    }

    // copy constructor
    customer_factory(const customer_factory& cf)

      :customer(cf), max_power_require(cf.max_power_require){}

    /*
    // istream
    customer_factory(istream& in){

      in>>*this;

    }
    */

    // operator overloading
    virtual const customer_factory& operator=(const customer_factory& cf){

      max_power_require = cf.max_power_require;

      customer::operator=(cf);

    }

    // destructor
    virtual ~customer_factory(){

      // delete_customer_factory(*supplier) // this is performed by base class

    }

    // instruction - please provide the ability to read and write the data.....

    friend ostream& operator<<(ostream& out, const customer_factory& cf); // stream output file

    friend istream& operator>>(istream& in, customer_factory& cf); // stream input file

    private:

        float max_power_require;

        power_company* supplier;

}; // class customer_factory

//------------------------------------------------------------------------------





ostream& operator<<(ostream& out,const customer_factory &cf){

      out<<cf.max_power_require;

      return(out);

}

istream& operator>>(istream& in,customer_factory &cf){

      in>>cf.max_power_require;

      return(in);

}


int main()
{

}
