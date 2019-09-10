// classes example
#include <iostream>
#include <cstring>
using namespace std;

void warn(const char msg[],bool endline=false){
	//see colors in
	//https://raccoon.ninja/pt/dev-pt/tabela-de-cores-ansi-python
cout << "\033[1;31mWARN: " << msg << "\033[m";
if(endline == true) cout << "\n";
}

void info(const char msg[], bool endline=false){
	//see colors in
	//https://raccoon.ninja/pt/dev-pt/tabela-de-cores-ansi-python
cout << "\033[1;94mINFO: " << msg << "\033[m";
if(endline == true) cout << "\n";
}

//rcout: red cout, true breaks the line
void rcout(const char msg[],bool endline=false){
	//see colors in
	//https://raccoon.ninja/pt/dev-pt/tabela-de-cores-ansi-python
cout << "\033[1;31m" << msg << "\033[m";
if(endline == true) cout << "\n";
}

//bcout: blue cout, true breaks the line
void bcout(const char msg[], bool endline=false){
	//see colors in
	//https://raccoon.ninja/pt/dev-pt/tabela-de-cores-ansi-python
cout << "\033[1;94m" << msg << "\033[m";
if(endline == true) cout << "\n";
}







class Matrix {
private:
	// attributes
	double **me; // the matrix pointer
	bool isdestroyed;
	int m; // number of rows
	int n; // number of columns
	// methods
	void throwisdestroyed(const char *);
	/* A private method for aborting the program when a
	 * destroyed matrix is being accessed.  It receives the name of
	 * the function that is calling it.
	 */
public:
	// methods
	void set(int,int,double); //method for setting the (i,j) entry//done
	double get(int,int); //method for getting the (i,j) entry//done
	Matrix mul(Matrix); //method for multiplying other matrix//done
	Matrix sum(Matrix); //method for summing with other matrix//done
	Matrix sub(Matrix); //method for subtracting with other matrix//done
	Matrix(int,int); //constructor method//done
	void fromuser(bool); //method for getting entries from user//done
	void print(); //method for printing the matrix//done
	bool isvector(); //returns true if m xor n is one
	void shape(); //prints the shape//done
	int shape1(); //returns the number of rows//done
	int shape2(); //returns the number of columns//done
	void destroy(); //it frees the memory and destroys the object//done
};

Matrix::Matrix(int nrows, int ncols){
	this->m = nrows;
	this->n = ncols;
	this->isdestroyed = false;
	
//allocating memory dynamically
	double **me = (double **) malloc(sizeof(double *) * this->m);
	this->me = me;
	if(this->me == NULL){
		warn("<Matrix::Matrix> says: It was not possible to allocate memory!\nFINNISHING...",true);
		throw "Class <Matrix> says: It was not possible to allocate memory!";
		exit(1);
	}
	
	for(int i = 0; i < this->m; i++){
		this->me[i] = (double *) malloc(sizeof(double) * this->n);
		if(this->me[i] == NULL){
			warn("<Matrix::Matrix> says: It was not possible to allocate memory!\nFINNISHING...",true);
			throw "Class <Matrix> says: It was not possible to allocate memory!";
			exit(1);
		}
	}

//setting all entries as zero
	for(int i = 0; i < this->m; i++){
		for(int j = 0; j < this->n; j++){
			this->me[i][j] = 0;
		}
	}
}


//getter
double Matrix::get(int i, int j){
	this->throwisdestroyed("get");
	if(i < 0 || i >= this->m || j < 0 || j >= this->n){
		warn("<Matrix:get> says: Indices are out of range!",true);
		throw "Class <Matrix> says: Indices are out of range!";
		exit(1);
	}
	return this->me[i][j];
}

//setter
void Matrix::set(int i, int j, double value){
	this->throwisdestroyed("set");
	if(i < 0 || i >= this->m || j < 0 || j >= this->n){
		warn("<Matrix:set> says: Indices are out of range!",true);
		throw "Class <Matrix> says: Indices are out of range!";
		exit(1);
	}
	this->me[i][j] = value;
}

//sum
Matrix Matrix::sum(Matrix mat){
	this->throwisdestroyed("sum");
	if(mat.m != this->m || mat.n != this->n){
		warn("<Matrix:sum> says: Dimensions for summing does not match!",true);
		throw "Class <Matrix> says: Dimensions for summing does not match!";
		exit(1);
	}
	Matrix answer(mat.m,mat.n);
	for(int i = 0; i < this->m; i++){
		for(int j = 0; j < this->n; j++){
			answer.set(i, j, this->get(i, j) + mat.get(i, j));
			}
		}
	return answer;
}

//sub
Matrix Matrix::sub(Matrix mat){
	this->throwisdestroyed("sub");
	if(mat.m != this->m || mat.n != this->n){
		warn("<Matrix:sub> says: Dimensions for subtracting does not match!",true);
		throw "Class <Matrix> says: Dimensions for subtracting does not match!";
		exit(1);
	}
	Matrix answer(mat.m,mat.n);
	for(int i = 0; i < this->m; i++){
		for(int j = 0; j < this->n; j++){
			answer.set(i, j, this->get(i, j) - mat.get(i, j));
			}
		}
	return answer;
}


//mul
Matrix Matrix::mul(Matrix mat){
	this->throwisdestroyed("mul");
	if(this->n != mat.m){
		warn("<Matrix:mul> says: Dimensions for multiplying does not match!",true);
		throw "Class <Matrix> says: Dimensions for multiplying does not match!";
		exit(1);
	}
	Matrix answer(this->m,mat.n);
	double summing;
	for(int i = 0; i < this->m; i++){
		for(int j = 0; j < mat.n; j++){
			summing = 0;
			for(int k = 0; k < this->n; k++){
				summing += this->get(i,k) * mat.get(k,j);
			}
		answer.set(i, j, summing);
		}
	}
	return answer;
}

//print
void Matrix::print(){
	this->throwisdestroyed("print");
	cout << "\033[1;100mMatrix object prints: ";
	this->shape();
	cout << " [\033[m\033[100;96m"<< endl;
	for(int i = 0; i < this->m; i++){
		cout << "   ";
		for(int j = 0; j < this->n; j++){
			cout << this->get(i,j) << "\t";
		}
		cout << "\n";
	}
	cout << "\033[m\033[1;100m]\033[m\n\n";
}


//fromuser
void Matrix::fromuser(bool cleardisplay=false){
	if(cleardisplay) system("clear");
	if(this->isdestroyed == false){
		double value;
		cout << "Getting entries of matrix from user" << endl;
		for(int i = 0; i < this->m; i++){
			cout << "Row: "<< i+1 << endl;
			for(int j = 0; j < this->n; j++){
				cout << "\tInsert the (" << i+1 << "," << j+1 << ")th element:\t";
				cin >>  value;
				this->set(i,j,value);
			}
			cout << "\n";
			
		}
	}else{
		warn("<Matrix:fromuser> Matrix was destroyed!",true);
	}
	if(cleardisplay) system("clear");
}

//shape
void Matrix::shape(){
cout << "Shape(" << this->m << "," << this->n << ")";
}

//shape1
int Matrix::shape1(){
return this->m;
}
//shape2
int Matrix::shape2(){
return this->n;
}

bool Matrix::isvector(){
if(this->shape1() == 1 || this->shape2() == 1 ){
	return true;
}else{
	return false;
}
}

//destroy
void Matrix::destroy(){
	if(this->isdestroyed == false){
		for(int i = 0; i < this->m; i++){
			free(this->me[i]);
		}
		free(this->me);
		info("Matrix is destroyed. Cannot be used anymore.",true);
		this->isdestroyed = true;
		this->m = -1;
		this->n = -1;
	}
}


//throwisdestroyed: private
void Matrix::throwisdestroyed(const char fname[]){
	if(this->isdestroyed == true){
		warn("<Matrix:");		
		rcout(fname);
		rcout("> Matrix was destroyed!",true);
		rcout("FINNISHING...",true);
		
		throw "Matrix was destroyed!";
		exit(1);
	}
}



int main () {
int i=2,j=2,k=3;
Matrix m(i,j), n(i,j), p(j,k), sum(i,j), sub(i,j), mult(j,k);

m.fromuser(true);//true makes clearing the display, empty dont
n.fromuser(true);
p.fromuser(true);

sum = m.sum(n);//makes m + n
sub = m.sub(n); // makes m - n
mult = m.mul(p); // makes m * p

rcout("soma",true); //red cout, true breaks the line
m.print(); 
n.print();
sum.print();


bcout("subtração",true); //blue cout, true breaks the line
m.print();
n.print();
sub.print();

bcout("multiplicação",true);
m.print();
p.print();
mult.print();


m.destroy();
p.destroy();
sum.destroy();
sub.destroy();
mult.destroy();
m.shape();
}
