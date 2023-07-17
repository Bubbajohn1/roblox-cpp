class test {
public:
    int val;
    int getVal() {
        return test::val;
    }
    void setVal(int newVal) {
        test::val = newVal;
    }
};