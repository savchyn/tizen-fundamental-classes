/*
 * DropDown.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Gilang M. Hamidy (g.hamidy@samsung.com)
 */

#ifndef SRIN_COMP_DROPDOWN_H_
#define SRIN_COMP_DROPDOWN_H_



#include "SRIN/Components/ComponentBase.h"
#include "SRIN/Components/Adapter.h"

namespace SRIN {
namespace Components {

/**
 * Component that provides dropdown menu.
 * It uses adapter pattern for appending and removing items,
 * and its class can map texts, contents and data of an item in the dropdown.
 */
class LIBAPI DropDown : public ComponentBase
{
private:
	Evas_Object* parentComponent;
	Evas_Object* dropdownComponent;
	Adapter* dataSource;

	EFL::EvasSmartEvent eventDropdownButtonClick;
	EFL::EvasSmartEvent eventDropdownDismiss;

	void SetDataSource(Adapter* adapter);
	Adapter* GetDataSource();

	void ShowDropdown();
	void OnDropDownButtonClick(EFL::EvasSmartEvent* viewSource, Evas_Object* objSource, void* eventData);
protected:
	/**
	 * Method overriden from ComponentBase, creates the UI elements of the component.
	 *
	 * @param root The root/parent given for this component.
	 *
	 * @return The dropdown's button.
	 */
	virtual Evas_Object* CreateComponent(Evas_Object* root);

public:
	/**
	 * Constructor for DropDown.
	 */
	DropDown();

	/**
	 * Method to programmatically select an item from the dropdown.
	 *
	 * @param item AdapterItem that will be selected.
	 */
	void ItemClick(Adapter::AdapterItem* item);

	/**
	 * Event that will be triggered when selected item in the dropdown changes.
	 */
	Event<DropDown*, void*> ItemSelectionChanged;

	/**
	 * Property that enables getting & setting the adapter of the dropdown.
	 * The return/parameter type is Adapter.
	 */
	Property<DropDown, Adapter*>::GetSet<&DropDown::GetDataSource, &DropDown::SetDataSource> DataSource;

	/**
	 * Property that enables reading of which item is selected in the dropdown.
	 * The return type is void*.
	 */
	Property<DropDown, void*>::Auto::ReadOnly SelectedItem;
	std::string text;
};

/**
 * Simplified AdapterItemClass that's specialized for use in DropDown.
 */
template<typename T>
class DropDownAdapter : public AdapterItemClass<T>
{
public:
	virtual std::string GetString(T* data, Evas_Object *obj, const char *part) final;
	virtual Evas_Object* GetContent(T* data, Evas_Object *obj, const char *part) final;
	/**
	 * Abstract method for providing text in dropdown item.
	 *
	 * @param data Adapter item's data.
	 *
	 * @return The text that will be displayed in item.
	 */
	virtual std::string GetText(T data) = 0;

	/**
	 * Abstract method for providing icon in dropdown item.
	 *
	 * @param data Adapter item's data.
	 *
	 * @return The Evas_Object that will be used as item icon.
	 */
	virtual Evas_Object* GetIcon(T* data, Evas_Object root) = 0;

	/**
	 * Destructor for DropDownAdapter.
	 */
	virtual ~DropDownAdapter() { };
};

}
}

template<typename T>
inline std::string SRIN::Components::DropDownAdapter<T>::GetString(T* data, Evas_Object* obj, const char* part)
{
	return GetText(data);
}

template<typename T>
inline Evas_Object* SRIN::Components::DropDownAdapter<T>::GetContent(T* data, Evas_Object* obj, const char* part)
{
	return GetIcon(data);
}

#endif /* DROPDOWN_H_ */
