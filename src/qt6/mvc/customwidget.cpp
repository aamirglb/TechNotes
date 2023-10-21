#include "customwidget.h"

QTextStream cout(stdout, QIODevice::WriteOnly);

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{
    m_View = new QListView(this);
    m_View->setAlternatingRowColors(true);

    m_Model = new QStringListModel(this);
    m_Text = new QLineEdit(this);
    // m_AddButton = new QPushButton("Add");
    // m_AddButton->setIcon(QIcon(":/images/assets/plus.png"));
    m_AddButton = new QPushButton(QIcon(":/images/assets/plus.png"), "");
    m_AddButton->setEnabled(false);

    // m_RemoveButton = new QPushButton("Remove");
    // m_RemoveButton->setIcon(QIcon(":/images/assets/minus.png"));
    m_RemoveButton = new QPushButton(QIcon(":/images/assets/minus.png"), "");
    m_RemoveButton->setEnabled(false);

    

    connect(m_Text, &QLineEdit::textChanged, this, &CustomWidget::textChanged);
    connect(m_Text, &QLineEdit::editingFinished, this, &CustomWidget::addRow);
    connect(m_AddButton, &QPushButton::clicked, this, &CustomWidget::addRow);
    connect(m_RemoveButton, &QPushButton::clicked, this, &CustomWidget::removeRow);

    m_View->setModel(m_Model);

    connect(m_View->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CustomWidget::selectionChanged);

    QList<QString> cities;
    cities << "Abu Dhabi" << "Dubai" << "Sharjah";
    m_Model->setStringList(cities);

    QHBoxLayout *row = new QHBoxLayout;
    // row->addWidget(m_Text);
    row->addWidget(m_AddButton);
    row->addWidget(m_RemoveButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_View);
    layout->addWidget(m_Text);
    layout->addLayout(row);
    this->setLayout(layout);
    cout << "Finished initialization." << Qt::endl;
}

void CustomWidget::textChanged(const QString& text)
{
    if(text.isEmpty())
    {
        m_AddButton->setEnabled(false);
    }
    else
    {
        m_AddButton->setEnabled(true);
    }
}

void CustomWidget::addRow()
{
    auto row = m_Model->rowCount();
    m_Model->insertRows(row, 1);
    auto idx = m_Model->index(row);
    // m_Model->setItemData(idx, QString("Ajman"));
    m_Model->setData(idx, m_Text->text());
    m_Text->setText("");
}

void CustomWidget::removeRow()
{
    auto index = m_View->currentIndex();
    if(index.isValid())
    {
        cout << "Index valid, removing " << index.row() << " row." << Qt::endl;
        m_Model->removeRows(index.row(), 1);
    }
}

void CustomWidget::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    cout << "Selection changed triggered." << Qt::endl;
    auto indexList = selected.indexes();
    if( indexList.size() > 0 )
    {
        m_RemoveButton->setEnabled(true);
    }
    else
    {
        m_RemoveButton->setEnabled(false);
    }
}