#include <QDialog>
#include "ui_key_bindings.h"
#include "core/hw/hid.h"



class QSettings;

/**
 * Register a hotkey.
 *
 * @param key Keyboard button
 * @param pad Name of the pad
 */

void RegisterKeyBinding(const QKeySequence keySeq, const HID::PAD pad);


/**
 * Saves all key bindings to the settings file.
 *
 *
 */
void SaveKeyBindings(QSettings& settings);


/**
* Get PAD associated with key event
*
*
*/
HID::PAD GetKeyBinding(QKeyEvent * event);

/**
 * Loads key bindings from the settings file.
 *
 *
 */
void LoadKeyBindings(QSettings& settings);


/**
* Sets default key bindings.
*
*
*/
void setDefaultKeyBindings();


class GKeyBindingsDialog : public QDialog
{
    Q_OBJECT

public:
	GKeyBindingsDialog(QWidget* parent = NULL);

private:
    Ui::key_bindings ui;

private slots:
    void updateItem(QTreeWidgetItem * item, int column);
};
