#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <typeinfo>
#include <type_traits>
using namespace std;
constexpr int PART_SIZE = 4; 

//builder pattern

struct Product
{
    std::array<std::string,5> vecPart;
    void print() {
        for(auto& s:vecPart){
            cout << s;
        }
    }
};

struct Builder
{
    virtual void buildPart1() = 0;
    virtual void buildPart2() = 0;
    virtual void buildPart3() = 0;
    virtual void buildPart4() = 0;    
};
struct ConcreteBuilder : public Builder
{
    Product* product;
    ConcreteBuilder() {
		reset();
	}
	~ConcreteBuilder() {
		delete product;
	}
    void buildPart1() {product->vecPart[0] = "part1";}
    void buildPart2() {product->vecPart[1] = "part2";}
    void buildPart3() {product->vecPart[2] = "part3";}
    void buildPart4() {product->vecPart[3] = "part4";}    
    void reset() {
        product = new Product; 
    }
    Product * getResult() {
        Product * result = product;
        reset();
        return result;
    }
};
struct Director
{
    Builder * builder;
    void setBuilder(Builder * b) { builder = b;}
    void buildMinimalProduct(){ builder->buildPart1();}
    void buildProduct(){ 
        builder->buildPart1();
        builder->buildPart2();
        builder->buildPart3();
        builder->buildPart4();
        }

};

int main()
{
    Director director;
    ConcreteBuilder * builder = new ConcreteBuilder;
    director.setBuilder(builder);
    director.buildMinimalProduct();
    director.buildProduct();
    ConcreteBuilder * blder = dynamic_cast<ConcreteBuilder *>(director.builder);
    blder->getResult()->print();

    return 0;
}