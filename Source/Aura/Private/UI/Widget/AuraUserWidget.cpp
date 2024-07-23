
#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	
	/*
	if we set the widget controller, we should do so with the setter (" WidgetControllerSet() " -> a blueprintimplementablevent)  and that way this will be kicked

off and we're safe to assume that when we implement widget controller set in any blueprint, we know

our widget controller will be set as it was just set.
	*/
	WidgetControllerSet();
}
