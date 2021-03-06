// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.


#include <map>
#include <QKeySequence>
#include <QStyledItemDelegate>
#include <QSettings>
#include <QKeyEvent>
#include "key_bindings.hxx"
#include "core/hw/hid.h"

typedef std::map<QKeySequence, HID::PAD> KeyBindingsMap;
KeyBindingsMap bindings;
typedef std::map<HID::PAD, QKeySequence> ReverseKeyBindingsMap;
ReverseKeyBindingsMap reverseBindings;


typedef std::map<HID::PAD, QString> NameMap;
NameMap names;
typedef std::map<QString, HID::PAD> ReverseNameMap;
ReverseNameMap reverseNames;

void SaveKeyBindings(QSettings& settings)
{
    settings.beginGroup("KeyBindings");

    for (auto key : bindings)
    {
        settings.setValue(key.first.toString(), key.second);
        settings.endGroup();
    }
    settings.endGroup();
}

void LoadKeyBindings(QSettings& settings)
{
    settings.beginGroup("KeyBindings");

    // Make sure NOT to use a reference here because it would become invalid once we call beginGroup()
    QStringList keys = settings.allKeys();
    for (QList<QString>::iterator key = keys.begin(); key != keys.end(); ++key)
    {
        settings.beginGroup(*key);
        QKeySequence keyseq = QKeySequence::fromString(settings.value("").toString());
    }

    settings.endGroup();
}

HID::PAD GetKeyBinding(QKeyEvent * event)
{
    QKeySequence keySeq = QKeySequence(event->text());
    return bindings[keySeq];
}

void RegisterKeyBinding(const QKeySequence keySeq, const HID::PAD pad)
{
    bindings[keySeq] = pad;
    reverseBindings[pad] = keySeq;
}

void createNameMap() {
    for (int i = 0; i < HID::g_num_pad_items; i++){ 
        names[(HID::PAD)(1 << i)] = QString(HID::PAD_NAMES[i]);
        reverseNames[QString(HID::PAD_NAMES[i])] = (HID::PAD)(1 << i);
    }
}

void setDefaultKeyBindings() {
    RegisterKeyBinding(QKeySequence("Y"), HID::PAD::PAD_A);
    RegisterKeyBinding(QKeySequence("H"), HID::PAD::PAD_B);
    RegisterKeyBinding(QKeySequence("Z"), HID::PAD::PAD_SELECT);
    RegisterKeyBinding(QKeySequence("X"), HID::PAD::PAD_START);

    RegisterKeyBinding(QKeySequence("W"), HID::PAD::PAD_UP);
    RegisterKeyBinding(QKeySequence("A"), HID::PAD::PAD_LEFT);
    RegisterKeyBinding(QKeySequence("S"), HID::PAD::PAD_DOWN);
    RegisterKeyBinding(QKeySequence("D"), HID::PAD::PAD_RIGHT);

    RegisterKeyBinding(QKeySequence("6"), HID::PAD::PAD_R);
    RegisterKeyBinding(QKeySequence("7"), HID::PAD::PAD_L);
    RegisterKeyBinding(QKeySequence("U"), HID::PAD::PAD_X);
    RegisterKeyBinding(QKeySequence("J"), HID::PAD::PAD_Y);

}

//class makes single columns uneditable
class NoEditDelegate : public QStyledItemDelegate {
public:
    NoEditDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        return 0;
    }
};

void GKeyBindingsDialog::updateItem(QTreeWidgetItem * item, int column) {
    bindings[item->text(1)] = reverseNames[item->text(0)]; //TODO: sanitise
    reverseBindings[reverseNames[item->text(0)]] = item->text(1);
    return;
}

GKeyBindingsDialog::GKeyBindingsDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);

    createNameMap();

    for (NameMap::iterator key = names.begin(); key != names.end(); ++key)
    {
        QKeySequence keySeq = reverseBindings[key->first];
        QStringList columns;
        columns << key->second << keySeq.toString();
        QTreeWidgetItem* item = new QTreeWidgetItem(columns);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
        ui.treeWidget->addTopLevelItem(item);

    }
    // TODO: Make context configurable as well (hiding the column for now)

    connect(
        this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
        this, SLOT(OnMouseDoubleClicked(QTreeWidgetItem*, int))
        );

    ui.treeWidget->resizeColumnToContents(0);
    ui.treeWidget->resizeColumnToContents(1);
    
    connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem *, int)),
        this, SLOT(updateItem(QTreeWidgetItem *, int)));
    ui.treeWidget->setItemDelegateForColumn(0, new NoEditDelegate(this));

}
