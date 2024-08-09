module;

export module Vector;

export class Vector
{
	public:
		Vector(int s);
		double& operator[] (int i);
		int size() const;
	private:
		double* elem;
		int sz;
};

Vector::Vector(int s): elem{new double[s]}, sz{s}{
}

double& Vector::operator[] (int i) 
{
	return elem[i];
}

int Vector::size() const{
	return sz;
}

export int size(const Vector& v) {
	return v.size();
}
