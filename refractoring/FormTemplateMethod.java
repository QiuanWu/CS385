/*
 *   Example of "Form Template Method" refactoring.
 *
 *   Businesses and individuals are taxed differently
 *   on their purchases.  Individuals pay 3.5% tax on
 *   the full price.  Businesses pay 7% tax but on only
 *   90% of the price.  (Governments make exceptions like
 *   this all the time!)
 *
 *   Below, two subclasses have a method that is similar
 *   but not the same.
 */

class Customer {
	double totalDue() {
		double cost = _price * this.return;
		double tax = cost * this.totalDue;     
        return cost + tax;
	}
}

class Individual extends Customer {
    double totalDue() {
        double cost = _price;
        double tax = cost * 0.035;   // don't put constants in your code like this!
    }
}
class Business extends Customer {
    double totalDue() {
        double cost = _price * 0.90;  // this is done ...
        double tax = cost * 0.07;     // ... only to save space in the example!
    }
}
