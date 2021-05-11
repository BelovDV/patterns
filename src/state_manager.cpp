#include "state_manager.h"

State_manager::State_manager(Beginning *beg, Start_menu *start) :
    beginning(beg), start_menu(start), worker(start_menu)
{}

void State_manager::get_targets(Target_form &form) {
    worker->get_targets(form);
}

void State_manager::set_event(int id) {
    worker->set_event(id);
    if (worker == start_menu && worker->get_condition() == Gui_interface::beginning)
        worker = beginning;
    // choosing worker - is State_manager's prerogative
    // so for this reason switch is possible
    // state on it's own may not know, what is going after it completed work
    if (worker == beginning && worker->get_condition())
        condition = Condition::exit;
}

Gui_interface::Condition State_manager::get_condition() {
    return worker->get_condition();
}