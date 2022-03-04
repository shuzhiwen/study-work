class String {
    char* pt;

   public:
    String();
    ~String();
    String(const char* str);
    String(const String& s);
    String& operator=(const String& s);

    void add(const String& s);  // 表示将s加到当前字符串中
    // 表示构造一个新字符串，内容为前字符串加上s，并返回该字符串对象
    String add(const String& s) const;
    void print() const;
};