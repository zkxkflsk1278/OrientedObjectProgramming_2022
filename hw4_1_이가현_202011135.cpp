#include <iostream>

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Pizza {
protected:
	string type;
	string orderID;
	string dough;
	string sauce;
	string toppings;

public:
	Pizza() { cout << "Pizza Default Constructor" << endl; }
	Pizza(string t, string oID) { type = t; orderID = oID; cout << "Pizza Constructor" << endl; };
	virtual ~Pizza() { cout << "Pizza Destructor" << endl; };
	void prepare() { cout << "Prepare all ingredients" << endl; };
	void bake() { cout << "Bake for 25 minutes at 350" << endl; };
	virtual void cut();
	void box() { cout << "Place pizza in official PizzaStore box" << endl; };
	string getType() { return type; };
	string getOrderID() { return orderID; };
};

void Pizza::cut() { cout << "Cutting the pizza into diagonal slices" << endl; };

class PaPaStyleCheesePizza : public Pizza {
public:
	PaPaStyleCheesePizza(string oID);
	~PaPaStyleCheesePizza() { cout << "PaPaStyleCheesePizza Destructor" << endl; };
};

PaPaStyleCheesePizza::PaPaStyleCheesePizza(string oID) {
	type = "PAPA Style Sauce and Cheese Pizza";
	sauce = "Marinara Sauce";
	dough = "Thin Crust Dough";
	toppings = "Grated Reggiano Cheese";
	orderID = oID;
}

class PaPaStylePepperoniPizza : public Pizza {
public:
	PaPaStylePepperoniPizza(string oID);
	~PaPaStylePepperoniPizza() { cout << "PaPaStylePepperoniPizza Destructor" << endl; };
};

PaPaStylePepperoniPizza::PaPaStylePepperoniPizza(string oID) {
	type = "PAPA Style Sauce and Pepperoni Pizza";
	sauce = "Marinara Sauce";
	dough = "Thin Crust Dough";
	toppings = "Grated Reggiano Cheese";
	orderID = oID;
};

class DominoStyleCheesePizza : public Pizza {
public:
	DominoStyleCheesePizza(string oID);
	~DominoStyleCheesePizza() { cout << "DominoStyleCheesePizza Destructor" << endl; };
	void cut() { cout << "Cutting the pizza into square slices" << endl; }; //override
};

DominoStyleCheesePizza::DominoStyleCheesePizza(string oID) {
	type = "Domino Style Deep Dish Cheese Pizza";
	sauce = "Plum Tomato Sauce";
	dough = "Extra Thick Crust Dough";
	toppings = "Shredded Mozzarella Cheese";
	orderID = oID;
};

class DominoStylePepperoniPizza : public Pizza {
public:
	DominoStylePepperoniPizza(string oID);
	~DominoStylePepperoniPizza() { cout << "DominoStylePepperoniPizza Destructor" << endl; };
	void cut() { cout << "Cutting the pizza into square slices" << endl; }; //override
};

DominoStylePepperoniPizza::DominoStylePepperoniPizza(string oID) {
	type = "Domino Style Deep Dish Pepperoni Pizza";
	sauce = "Plum Tomato Sauce";
	dough = "Extra Thick Crust Dough";
	toppings = "Shredded Mozzarella Cheese";
	orderID = oID;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


class DeliveryProcessing {
private:
	int maxNumOrder;
	Pizza** deliveryQueue; //Array of Pizza pointers
	int front{ -1 };
	int rear{ -2 };

public:
	DeliveryProcessing(int maxOrder) { maxNumOrder = maxOrder; deliveryQueue = new Pizza*; };
	~DeliveryProcessing();
	int addOrder(Pizza* newOrder);
	int deliverOrder();
};

DeliveryProcessing::~DeliveryProcessing() {
	for (int i = 0; i < this->maxNumOrder; i++) {
		delete deliveryQueue[i];
	}
	delete[] deliveryQueue;
}

int DeliveryProcessing::addOrder(Pizza* newOrder) {
	if ((rear - front + 1) < maxNumOrder) {
		if ((rear - front + 1) == 0) {
			deliveryQueue[0] = newOrder;
			front = 0;
			rear = 0;
			cout << "[" << deliveryQueue[0]->getType() << "] is ordered by [" << deliveryQueue[0]->getOrderID() << "]" << endl;
		}
		else {
			deliveryQueue[rear + 1] = newOrder;
			cout << "[" << deliveryQueue[rear + 1]->getType() << "] is ordered by [" << deliveryQueue[rear + 1]->getOrderID() << "]" << endl;
			rear++;
		};
		return 1;
	}
	else {
		cout << "Queue is full" << endl;
		delete newOrder;
		return 0;
	};
};

int DeliveryProcessing::deliverOrder() {
	if ((rear - front + 1) == 0) {
		cout << "Queue is empty" << endl;
		return 0;
	}
	else {
		cout << "[" << deliveryQueue[front]->getType() << "] is delivered to [" << deliveryQueue[front]->getOrderID() << "]" << endl;
		delete deliveryQueue[front];
		front++;
		return 1;
	};
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PizzaStore {
protected:
	int numOfDeliveryCar;
	DeliveryProcessing* myDeliveryProcessing;
	static int OrderCnt;

public:
	PizzaStore();
	PizzaStore(int n);
	virtual ~PizzaStore() = 0;
	Pizza* orderPizza(string type, string orderID);
	virtual Pizza* createPizza(string type, string orderID) = 0;
	DeliveryProcessing* getDeliveryProcessingHandler() { return myDeliveryProcessing; };
	int getTotalOrderCnt() { cout << "Total orders so far: " << OrderCnt << endl; return OrderCnt; };
	string operator[](int index);
};

PizzaStore::~PizzaStore() { cout << "PizzaStore Destructor" << endl; };

PizzaStore::PizzaStore() {
	cout << "PizzaStore constructor" << endl;
	numOfDeliveryCar = 10;
	myDeliveryProcessing = new DeliveryProcessing(numOfDeliveryCar);
};

PizzaStore::PizzaStore(int n) {
	cout << "PizzaStore constructor" << endl;
	numOfDeliveryCar = n;
	myDeliveryProcessing = new DeliveryProcessing(numOfDeliveryCar);
};

Pizza* PizzaStore::createPizza(string type, string orderID) {
	return new Pizza(type, orderID);
}

Pizza* PizzaStore::orderPizza(string type, string orderID) {
	Pizza* pizza{ createPizza(type, orderID) };
	OrderCnt++;
	getTotalOrderCnt();
	(*pizza).prepare();
	(*pizza).bake();
	(*pizza).cut();
	(*pizza).box();
	return pizza;
};


class PaPaPizzaStore : public PizzaStore {
public:
	PaPaPizzaStore() { cout << "PaPaPizzaStore constructor" << endl; };
	~PaPaPizzaStore() { cout << "PaPaPizzaStore destructor" << endl; };
	Pizza* createPizza(string item, string orderID);
};

Pizza* PaPaPizzaStore::createPizza(string item, string orderID) {
	if (item == "cheese") {
		PaPaStyleCheesePizza* pizza;
		pizza = new PaPaStyleCheesePizza(orderID);
		return pizza;
	}
	else {
		PaPaStylePepperoniPizza* pizza;
		pizza = new PaPaStylePepperoniPizza(orderID);
		return pizza;
	}
};


class DominoPizzaStore : public PizzaStore {
public:
	DominoPizzaStore() { cout << "DominoPizzaStore constructor" << endl; };
	~DominoPizzaStore() { cout << "DominoPizzaStore destructor" << endl; };
	Pizza* createPizza(string item, string orderID);
};

Pizza* DominoPizzaStore::createPizza(string item, string orderID) {
	if (item == "cheese") {
		DominoStyleCheesePizza* pizza;
		pizza = new DominoStyleCheesePizza(orderID);
		return pizza;
	}
	else {
		DominoStylePepperoniPizza* pizza;
		pizza = new DominoStylePepperoniPizza(orderID);
		return pizza;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


int PizzaStore::OrderCnt = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
	PizzaStore* papaStore = new PaPaPizzaStore();
	PizzaStore* dominoStore = new DominoPizzaStore();
	Pizza* pizza_papa_1 = papaStore->orderPizza("cheese", "tom");
	cout << pizza_papa_1->getType() << endl;
	papaStore->getDeliveryProcessingHandler()->addOrder(pizza_papa_1);
	cout << "PaPaStore[0]: " << (*papaStore)[0] << "PaPaStore[1]: " << (*papaStore)[1] << endl;
	Pizza* pizza_papa_2 = papaStore->orderPizza("pepperoni", "nick");
	cout << pizza_papa_2->getType() << endl;
	papaStore->getDeliveryProcessingHandler()->addOrder(pizza_papa_2);
	cout << "PaPaStore[0]: " << (*papaStore)[0] << "PaPaStore[1]: " << (*papaStore)[1] << endl;
	Pizza* pizza_domino_1 = dominoStore->orderPizza("cheese", "jenny");
	cout << pizza_domino_1->getType() << endl;
	Pizza* pizza_domino_2 = dominoStore->orderPizza("pepperoni", "kate");
	cout << pizza_domino_2->getType() << endl;
	dominoStore->getDeliveryProcessingHandler()->addOrder(pizza_domino_1);
	dominoStore->getDeliveryProcessingHandler()->addOrder(pizza_domino_2);
	cout << "DominoStore[0]: " << (*dominoStore)[0] << "DominoStore[1]: " << (*dominoStore)[1] << endl;
	papaStore->getDeliveryProcessingHandler()->deliverOrder();
	dominoStore->getDeliveryProcessingHandler()->deliverOrder();
	cout << "PaPaStore[0]: " << (*papaStore)[0] << "PaPaStore[1]: " << (*papaStore)[1] << endl;
	cout << "DominoStore[0]: " << (*dominoStore)[0] << "DominoStore[1]: " << (*dominoStore)[1] << endl;
	return 0;	
}