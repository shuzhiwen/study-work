class A {
   public:
    A() { n = 0; }
    int n;
};

class share {
   public:
    share();
    explicit share(A* p1);
    ~share();
    share(share& t2);
    share& operator=(share& t2);
    A* operator->();
    A& operator*();

   private:
    A* point;
};
