#include <QList>

class Node {
public:
    enum Type { Root, 
                OrExpression, 
                AndExpression, 
                NotExpression, 
                Atom, 
                Identifier,
                Operator,
                Punctuator
            };

    Node(Type type, const QString &str = "");
    ~Node();

    Type type;
    QString str;
    Node *parent;
    QList<Node *> children;
};
