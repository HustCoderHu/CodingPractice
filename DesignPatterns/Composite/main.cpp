#include <iostream>
#include <vector>

using namespace std;



/*
Component抽象基类，为组合中的对象声明接口,声明了类共有接口的缺省行为(如这里的Add,Remove,GetChild函数),
声明一个接口函数可以访问Component的子组件.
*/
class Component
{
public:
    //纯虚函数，只提供接口，没有默认的实现
    virtual void Operation() = 0;

    // 虚函数,提供接口,有默认的实现就是什么都不做
    virtual void Add(Component*) {
        cout << "add" << endl;
    }

    virtual void Remove(Component*) {}
    virtual Component* GetChild(int index) {
        return nullptr;
    }

    virtual ~Component() {}
protected:
    Component() {}
};

// 安全组合模式
//Leaf是叶子结点,也就是不含有子组件的结点类，所以不用实现Add、Remove、GetChild等方法
class Leaf:public Component
{
public:
    Leaf() {}
    ~Leaf() {}

    //只实现Operation接口
    virtual void Operation() {
        cout << "Leaf::Operation" << endl;
    }
};
// 透明组合模式 Leaf 与 Composite 所提供的接口一致，Client 可以相同地对待所有的对象。


//Composite：含有子组件的类
class Composite:public Component
{
public:
    Composite() {}
    ~Composite() {}
    //实现所有接口
    void Operation() {
        cout << "Composite::Operation" << endl;
        for (auto &iter : m_ComVec)
            iter->Operation();
    }

    void Add(Component *com) {
        m_ComVec.push_back(com);
    }

    void Remove(Component*) {}
    Component* GetChild(int index) {
        if(index < 0 || index > m_ComVec.size())
            return nullptr;
        return m_ComVec[index];
    }

private:
    //这里采用vector来保存子组件
    vector<Component*> m_ComVec;
};


int main(int argc, char *argv[])
{
    Composite* pRoot = new Composite();

    //组合对象添加叶子节点
//    pRoot->Add(new Leaf());

    Leaf* pLeaf1 = new Leaf();
    Leaf* pLeaf2 = new Leaf();
    //这里的叶子再添加叶子是没有意义的。
    //由于叶子与组合对象继承了相同的接口，所以语法上是对的，实际上什么也没做(继承自基类Component的Add方法)。
    //叶子节点只实现了Operation方法，其他Add、Remove、GetChild都继承自基类，没有实际意义。
    pLeaf1->Add(pLeaf2);
    pLeaf1->Remove(pLeaf2);
    //执行叶子Operation操作
    pLeaf1->Operation();

    //组合对象实现了基类Component的所有接口，所以可以做各种操作(Add、Remove、GetChild、Operation)。
    Composite* pCom = new Composite();
    //组合对象添加叶子节点
    pCom->Add(pLeaf1);
    //组合对象添加叶子节点
    pCom->Add(pLeaf2);
    //执行组合对象Operation操作
    pCom->Operation();

    //组合对象添加组合对象
    pRoot->Add(pCom);

    //执行组合对象Operation操作
    pRoot->Operation();

    //Component* cp = pCom->GetChild(0);
    //cp->Operation();

    //pCom->Remove(pLeaf1);

    delete pLeaf1;
    delete pLeaf2;
    delete pCom;
    delete pRoot;

    return 0;
}

// www.cnblogs.com/onlycxue/p/3483234.html
