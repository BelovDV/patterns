#include "ai.h"
#include "database_loader.h"

AI::AI() {}

void AI::generate_position(Position* pos) {
    srand(1);
    int class_id = rand() % 3;
    int race_id = (pos->get_race(Position::Player::player1) == 0 ? 1 : 0);
    pos->set_class(Position::Player::player2, class_id);
    pos->set_race(Position::Player::player2, race_id);

    auto c_data = database.get_classes()[class_id];
    std::vector<int> p_money(3);
    p_money[0] = c_data.start_money_A;
    p_money[1] = c_data.start_money_B;
    p_money[2] = c_data.start_money_C;

    auto& unit_ids = database.get_races_units()[race_id];
    int types = unit_ids.size();

    for (int i = 0; i != 1000; ++i)
    {
        int i_u_id = rand() % types;
        const Data::Unit::Data& unit_data = database.get_units()[unit_ids[i_u_id]];
        if (p_money[0] >= unit_data.cost_A && p_money[1] >= unit_data.cost_B && p_money[2] >= unit_data.cost_C)
        {
            p_money[0] -= unit_data.cost_A;
            p_money[1] -= unit_data.cost_B;
            p_money[2] -= unit_data.cost_C;
            pos->add_unit(Position::player2,Unit(database.get_races_units()[race_id][i_u_id]));
        }
    }
}