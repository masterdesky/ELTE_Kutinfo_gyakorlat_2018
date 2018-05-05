class Parent
{
  virtual ~Parent(); //virtual destructor to ensure our subclasses are correctly deallocated
};

class Type1 : public Parent
{
    void type1method();
};

class Type2 : public Parent
{
    void type2Method();
};


class Type3 : public Parent
{
    void type3Method();
}