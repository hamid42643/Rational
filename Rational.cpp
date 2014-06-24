#include <iostream>

//for string manipulation
#include <string>
#include <vector>
#include <functional>


using namespace std;

class Rational{
private:
	int numerator; //soorat
	int denominator; //makhraj
	string input;
	

public:
	int dontPrintDen;
	int error;
	Rational();
	Rational(int, int);
	Rational(int);
//	Rational::Rational(int, const 1);
	
	bool Rational::anyError();
	bool isNumber(const std::string& );
	void Rational::normalize(bool);


	//Overloaded operator functions 
	Rational operator + (const Rational &);
	Rational operator - (const Rational &); 
	Rational operator / (const Rational &); 
	Rational operator * (const Rational &);

	bool Rational:: operator  ==  (const Rational &);
	bool Rational:: operator  >  (const Rational &);
	bool Rational:: operator  <  (const Rational &);

	/*
	function prototypes for overloaded stream operators 
	Both functions attempt to directly access the Rational object's private members. Because 
	These functions aren't themselves members of the Rational class, they don't have this type 
	Of access so the operators should be friend of the Rational class.
	*/
	friend ostream &operator << (ostream & , Rational &);
	friend istream &operator >> (istream & , Rational &);

};
//----------------------------------------------

//default constructor
Rational::Rational(){
	numerator = 0;
	denominator = 1;
}

//first constructor
Rational::Rational(int n, int d){  
	numerator = n;
	denominator = d;
}
//second constructor
Rational::Rational(int n){  
	numerator = n;
	denominator = 1;
}



/*
checkes the private varible error if its set to 1 the function returns true
*/
bool Rational::anyError(){
	if(this->error==1){
		this->error=0;
		return true;

	}
	else{
		return false;
	}
}

/*
ths function first counts the numbers of '/' '-' and '+' if it is more than 1 or 2 it returns false.
also if after '+' or '-' there is a non-degit character or a '0' it returns false(ex -+23/33)
also if there is any none-digit character in the string array it returns false
*/
bool isNumber(const std::string& s)
{
	int countSlash=0;
	int countPlus=0;
	int countMinus=0;

	if(s[0]=='0'){
		return false;
	}

	for (unsigned int i = 0; i < s.length(); i++) 
	{
		if((s[i]=='/'))
		{ 
			countSlash++;
			if(s[i+1]=='0'){
				return false;
			}
		}
		else if((s[i]=='+'))
		{ 
			countPlus++;
			if((!isdigit(s[i+1]))||(s[i+1]=='0')){
				return false;
			}
		}
		else if((s[i]=='-'))
		{ 
			countMinus++;
			if((!isdigit(s[i+1]))||(s[i+1]=='0')){
				return false;
			}
		}
		else if(!isdigit(s[i]))
		{ 
			return false;

		}
	}

	if(countSlash>1){
		return false;
	}
	if(countPlus>2){
		return false;
	}
	if(countMinus>2){
		return false;
	}

	return true;

}


/*
this function fix the sign(for example -4/-3 becomes 4/3), and also find the greater common devisor and divides the
numerator and denominator by it. if the boolean i is set to 1 it only tries to fix the sign.
*/
void Rational::normalize(bool i=0){ 
	int a = numerator;
	int b = denominator;

	int sign = 1;
	if (a < 0) { sign = sign * -1; numerator = -numerator; a=-a;}       
	if (b < 0) { sign = sign * -1;  denominator = -denominator; b=-b;}

	if((i==0))
	{
		if((b!=0)&&(a!=0))//if eighter numerator or denominator are not zeros
		{
			int tmp, rem=1, gcd;
			if(a>b){
				tmp=a;
				a=b;
				b=tmp;
			}
			while(rem>0){
				rem=b%a;
				b=a;
				gcd=a;
				a=rem;
			}
			numerator = sign*(numerator/gcd);
			denominator = denominator/gcd;
			if(denominator==1){//updated
				dontPrintDen=1;
			}
		}else{
			numerator = sign*(numerator);
			denominator = denominator;
			dontPrintDen=1;
		}
	}else{
		numerator = sign*(numerator);
		denominator = denominator;
	}
}




/*
Overloading + operator
This function is called anytime the + operator is used with two Rational objects.
This function has one parameter: a constant reference object named 'right'. This parameter references the object 
on the right side of the operator, For example, when the following statement is executed, 
right will reference the b object: 
a + b
*/
Rational Rational::operator +(const Rational &right){ 
	Rational temp;
	temp.numerator = (numerator * right.denominator) + (right.numerator * denominator);
	temp.denominator = denominator * right.denominator;
	temp.normalize();
	return temp; 
}

//Overloading - operator
Rational Rational::operator - (const Rational &right) { 
	Rational temp;
	temp = Rational(numerator*right.denominator - right.numerator*denominator, denominator*right.denominator);
	temp.normalize();
	return temp; 
}

//Overloading * operator
Rational Rational::operator * (const Rational &right) { 
	Rational temp;
	temp =  Rational(numerator * right.numerator, denominator * right.denominator);
	temp.normalize();
	return temp;
}


//Overloading / operator
Rational Rational::operator / (const Rational &right) { 
	Rational temp;
	temp = Rational(numerator * right.denominator, denominator * right.numerator);
	temp.normalize();
	return temp;
}

//Overloading == operator
bool Rational:: operator  ==  (const Rational &right) {
return (numerator * right.denominator == denominator * right.numerator); 
}

//Overloading > operator
bool Rational:: operator  >  (const Rational &right) {
bool c  (numerator * right.denominator > denominator * right.numerator); 
return c;
}

//Overloading < operator
bool Rational:: operator  <  (const Rational &right) {
bool c = (numerator * right.denominator < denominator * right.numerator); 
return c;
}

/*
Overloading << operator,
This function tells C++ how to handle any expression that has the Following form:
Left		     Right
ostreamObject << RationalObject
When the return strm; statement executes, it doesn’t return a copy of strm, but a reference to it. 
This allows to chain together several expressions using the overloaded operator

NOTE: Do not confuse the address operator(pointers chapter) with the & symbol used when defining a 
refrence
*/
ostream &operator << (ostream &strm, Rational &right){
	if(right.dontPrintDen==1){
		cout << right.numerator;
		right.normalize(1);
		return strm;
	}else{
		cout << right.numerator << "/" << right.denominator;
		right.normalize(1);
		return strm;
	}
}

//Overloading >> operator, this function gets user input
istream &operator >> (istream &strm, Rational &right){ 
	//char slash;
	//strm >> right.numerator >> slash >> right.denominator;

	//cout << "enter the rational number: ";
	
	char line[233];
	cin.getline(line,233);


	if(isNumber(line)){ // check if input is valid
		right.input = line;
		int slashPos = right.input.find("/");
		int num,den;

		if(slashPos!=-1){ //if '/' exists
			string n = right.input.substr(0, slashPos);
			string d = right.input.substr(slashPos+1);
			num = atoi(n.c_str());
			den = atoi(d.c_str());
		}
		else{// if '/' doesnt exist we suppose users entering rational number as whole(ex 5 instead of 5/1)
			string n = right.input;
			num = atoi(n.c_str());
			den=0;
		}

		if(num==0){ // if numerator doesn't exist or it's not a number
			right.error=1;
			return strm;
		}else if(den==0) // if denominator doesn't exist or it's not a number
		{
			if(slashPos==-1){ //// if '/' doesn't exist
				right.numerator = num;
				right.denominator = 1;
				right.normalize(1);
				//right.dontPrintDen=1;
				return strm;
			}else{
				right.error=1;
				return strm;

			}
		}else{ // if both numerator and denominator exist and both are numbers
			right.numerator = num;
			right.denominator = den;
			right.normalize(1);
			return strm;

		}
	}else{
		right.error=1;
		return strm;
	}
}




void main(){
	/*
	Rational a(2);
	Rational b(-1,-3);

	a.normalize(a,1);
	b.normalize(b,1);
	*/

	while(1){
		bool error=1;
		Rational a,b;

		while(error==1){
			//Rational a;
			cout << "enter the first rational number: ";
			cin >> a;
			if(a.anyError()){
				error=1;
				cout << "\nfirst rational number is invalid!\n";
			}else{
				break;
			}
		}

		while(error==1){
			//Rational b;
			cout << "enter the second rational number: ";
			cin >> b;
			if(b.anyError()){
				error=1;
				cout << "\nsecond rational number is invalid!\n";
			}else{
				break;
			}
		}

		if(a == b){
			cout << a << " = " << b << endl;
		}else{
			cout << a << " is not = " << b << endl;
		}

		if(a > b){
			cout << a << " > " << b << endl;
		}else{
			cout << a << " is not > " << b << endl;
		}

		if(a < b){
			cout << a << " < " << b << endl;
		}else{
			cout << a << " is not < " << b << endl;
		}

		cout << "(" << a << ")" << " + " << "(" << b << ")" <<" = " << a + b << endl;
		cout << "(" << a << ")" << " - " << "(" << b << ")" <<" = " << a - b << endl;
		cout << "(" << a << ")" << " * " << "(" << b << ")" <<" = " << a * b << endl;
		cout << "(" << a << ")" << " / " << "(" << b << ")" <<" = " << a / b << endl;
		getchar();

	}

	
}
