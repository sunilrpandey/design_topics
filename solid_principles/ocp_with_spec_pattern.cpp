#include <iostream>
#include <vector>

using namespace std;

enum class Color
{
	red, green, blue
};
enum class Size
{
	small, medium, big
};
struct Product
{
	std::string name;
	Color color;
	Size size;
};
struct ProductFilter
{
	using Items = std::vector<Product*>;
	Items by_color(Items items, Color color) {
		Items result;
		for (auto& r : items) {
			if (r->color == color)
				result.push_back(r);
		}
		return result;
	}
	Items by_size(Items items, Size size) {
		Items result;
		for (auto& r : items) {
			if (r->size == size)
				result.push_back(r);
		}
		return result;
	}
	Items by_color_size(Items items,Color color, Size size) {
		Items result;
		for (auto& r : items) {
			if (r->size == size && r->color == color)
				result.push_back(r);
		}
		return result;
	}
};
template<typename T>
struct ISpecification {
	virtual bool is_satisfied(T* item) = 0;
};

struct ColorSpecification : ISpecification<Product>
{
	Color color;
	explicit ColorSpecification(Color c) {
		color = c;
	}
	bool is_satisfied(Product* p) {
		return p->color == color;
	}
};
struct SizeSpecification : ISpecification<Product>
{
	Size size;
	explicit SizeSpecification(Size s) {
		size = s;
	}
	bool is_satisfied(Product* p) {
		return p->size== size;
	}
};
struct AndSpecification : ISpecification<Product>
{
	ISpecification<Product>& first;
	ISpecification<Product>& second;
	explicit AndSpecification(ISpecification<Product>& f, ISpecification<Product>& s) :first(f), second(s)
	{		
	}
	bool is_satisfied(Product* p) {
		return first.is_satisfied(p) && second.is_satisfied(p);
	}
};

template<typename T>
struct IFilter {
	virtual vector<T*> filter(vector<T*>items, ISpecification<T>& spec) = 0;
};
struct BetterFilter : public IFilter<Product>
{
	using Items = vector<Product*>;
	Items filter(Items items, ISpecification<Product>& spec) {
		Items result;
		for (auto& r : items) {
			if (spec.is_satisfied(r)) {
				result.push_back(r);
			}
		}
		return result;
	}
};

int main()
{
	Product apple{ "apple",Color::green,Size::small };
	Product tree{ "tree", Color::green, Size::big };
	Product house{ "house",Color::blue,Size::big };
	std::vector<Product*> all{ &apple, &tree, &house };
	ColorSpecification clrType{Color::green};
	BetterFilter bf;
	vector<Product*> items = bf.filter(all, clrType);
	cout << "Demo : Color Filter Demo" << endl;
	for (auto& i : items) {
		cout << i->name.c_str() << endl;
	}
	SizeSpecification szType{ Size::big};
	items = bf.filter(all, szType);
	cout << "Demo : Size Filter Demo" << endl;
	for (auto& i : items) {
		cout << i->name.c_str() << endl;
	}
	AndSpecification andType(clrType, szType);
	items = bf.filter(all, andType);
	cout << "Demo : And Filter Demo" << endl;
	for (auto& i : items) {
		cout << i->name.c_str() << endl;
	}
	return 0;
}