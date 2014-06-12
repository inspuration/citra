/********************************************************************************
** Form generated from reading UI file 'key_bindings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEY_BINDINGS_H
#define UI_KEY_BINDINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_key_bindings
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *key_bindings)
    {
        if (key_bindings->objectName().isEmpty())
            key_bindings->setObjectName(QString::fromUtf8("key_bindings"));
        key_bindings->resize(363, 388);
        verticalLayout = new QVBoxLayout(key_bindings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(key_bindings);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeWidget->setHeaderHidden(false);

        verticalLayout->addWidget(treeWidget);

        buttonBox = new QDialogButtonBox(key_bindings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Reset);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(key_bindings);
        QObject::connect(buttonBox, SIGNAL(accepted()), key_bindings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), key_bindings, SLOT(reject()));

        QMetaObject::connectSlotsByName(key_bindings);
    } // setupUi

    void retranslateUi(QDialog *key_bindings)
    {
        key_bindings->setWindowTitle(QApplication::translate("key_bindings", "Key Bindings", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("key_bindings", "Pad", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("key_bindings", "Key", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("key_bindings", "Action", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class key_bindings: public Ui_key_bindings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEY_BINDINGS_H
