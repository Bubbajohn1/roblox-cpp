-- extra functions to help with the conversion

--[[

EXAMPLE CLASS IN LUA

function TestClass.new()
    --Create the base object.
    local Object = {Value = 2}
    setmetatable(Object,TestClass)
    TestClass.__index = TestClass

    --Return the object.
    return Object
end

function TestClass:GetValue()
    return self.Value
end

--Create an instance of the class.
local TestObject = TestClass.new()
print(TestObject:GetValue()) --2

]]







--[[

CPP:

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
};

LUA:

local test = {}

function test.new()
    local Object = {val = 0}
    setmetatable(Object,test)
    test.__index = test

    --Return the object.
    return Object
end

function test:getVal()
    return self.val
end

function test:setVal(newVal)
    self.val = newVal
end

]]

local RPP = {}

function RPP.Include(includePath)

end

function RPP.MakeEnum()
    
end

return RPP