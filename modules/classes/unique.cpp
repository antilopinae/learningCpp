void user(int х)
{
    Shape* р = new Circle{Point{0,0},10};
    if (х<О) throw Bad_x{}; //Потенциальная утечка
    if (х==О) return;
    // Потенциальная утечка
    delete р;
}

// Надо так
class Smiley : public Circle
{
    / / ...
private:
    vector<unique_ptr<Shape>> eyes; // удалятся сами даже если забудем
    unique_ptr<Shape> mouth;
} ;

enum class Kind { circle, triangle, smiley };

unique_ptr<Shape> read_shape(istream& is)
{
    // Читаем заголовок фигуры из is и находим ее в Kind k
    switch (k)
    {
        case Kind::circle:
            return unique_ptr<Shape>{new Circle{p,r}};
    }
}

void user()
{
    vector<unique_ptr<Shape>> v;
    while (cin)
        v.push_back(read_shape(cin));
    draw_all(v);
    rotate_all(v,45);
}
