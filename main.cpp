#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <json.hpp>  // Include the JSON library

using json = nlohmann::json;

// Function to roll the die based on given probabilities
int roll_special_die(const double probabilities[]) {
    double cumulative_probabilities[7];
    cumulative_probabilities[0] = probabilities[0];
    for (int i = 1; i < 7; ++i) {
        cumulative_probabilities[i] = cumulative_probabilities[i - 1] + probabilities[i];
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    double rand_value = dis(gen);

    for (int i = 0; i < 7; ++i) {
        if (rand_value <= cumulative_probabilities[i]) {
            return i + 1; // Return 1 to 7 as the roll result
        }
    }
    return 7; // This should theoretically never be reached because of the 100% probability
}

// Card structure for each pack
struct Pack {
    std::string name;
    std::vector<std::string> common_card;
    std::vector<std::string> crown_card;
    std::vector<std::string> three_star_card;
    std::vector<std::string> two_star_card;
    std::vector<std::string> one_star_card;
    std::vector<std::string> four_diamond_card;
    std::vector<std::string> three_diamond_card;
    std::vector<std::string> two_diamond_card;
};

// Function to load packs from a JSON file
std::vector<Pack> load_packs_from_file(const std::string& filename) {
    std::ifstream file(filename);
    json json_data;
    file >> json_data;

    std::vector<Pack> packs;
    for (const auto& pack_data : json_data["packs"]) {
        Pack pack;
        pack.name = pack_data["name"];
        pack.common_card = pack_data["common_card"].get<std::vector<std::string>>(); 
        pack.crown_card = pack_data["crown_card"].get<std::vector<std::string>>(); 
        pack.three_star_card = pack_data["three_star_card"].get<std::vector<std::string>>(); 
        pack.two_star_card = pack_data["two_star_card"].get<std::vector<std::string>>(); 
        pack.one_star_card = pack_data["one_star_card"].get<std::vector<std::string>>(); 
        pack.four_diamond_card = pack_data["four_diamond_card"].get<std::vector<std::string>>(); 
        pack.three_diamond_card = pack_data["three_diamond_card"].get<std::vector<std::string>>(); 
        pack.two_diamond_card = pack_data["two_diamond_card"].get<std::vector<std::string>>(); 

        packs.push_back(pack);
    }

    return packs;
}

// Function to save the chosen cards to a file
void save_chosen_cards(const std::vector<std::string>& chosen_cards) {
    std::ofstream file("obtained_cards.txt", std::ios::app); // Open file in append mode
    for (const auto& card : chosen_cards) {
        file << card << std::endl;  // Write each card on a new line
    }
    file << "------------------------\n";  // Separator for each pack opening
}

// Function to open a pack and draw 5 cards
void open_pack(const Pack& selected_pack) {
    std::cout << "" << std::endl;

    // Create a random number generator for common cards
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_common(0, selected_pack.common_card.size() - 1);

    std::vector<std::string> chosen_cards;
    

    // 1st, 2nd, and 3rd card are common cards
    for (int i = 0; i < 3; ++i) {
        int common_card_idx = dis_common(gen); // Select a random common card
        chosen_cards.push_back(selected_pack.common_card[common_card_idx]);  // Add to chosen cards
        std::cout << "Common - " << selected_pack.common_card[common_card_idx] << std::endl;
    }

    // Roll for the 4th card (same process for rarity distribution)
    double probabilities_fourth[] = {0.040, 0.222, 0.500, 2.572, 1.666, 5.000, 90.000};
    int fourth_roll_result = roll_special_die(probabilities_fourth);

    switch (fourth_roll_result) {
        case 1: {
            std::uniform_int_distribution<> dis(0, selected_pack.crown_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.crown_card[index]);
            std::cout << "God - " << selected_pack.crown_card[index] << std::endl;
            break;
        }
        case 2: {
            std::uniform_int_distribution<> dis(0, selected_pack.three_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.three_star_card[index]);
            std::cout << "Mythic - " << selected_pack.three_star_card[index] << std::endl;
            break;
        }
        case 3: {
            std::uniform_int_distribution<> dis(0, selected_pack.two_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.two_star_card[index]);
            std::cout << "Legendary - " << selected_pack.two_star_card[index] << std::endl;
            break;
        }
        case 4: {
            std::uniform_int_distribution<> dis(0, selected_pack.one_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.one_star_card[index]);
            std::cout << "Epic - " << selected_pack.one_star_card[index] << std::endl;
            break;
        }
        case 5: {
            std::uniform_int_distribution<> dis(0, selected_pack.four_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.four_diamond_card[index]);
            std::cout << "Ultra Rare - " << selected_pack.four_diamond_card[index] << std::endl;
            break;
        }
        case 6: {
            std::uniform_int_distribution<> dis(0, selected_pack.three_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.three_diamond_card[index]);
            std::cout << "Rare - " << selected_pack.three_diamond_card[index] << std::endl;
            break;
        }
        case 7: {
            std::uniform_int_distribution<> dis(0, selected_pack.two_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.two_diamond_card[index]);
            std::cout << "Uncommon - " << selected_pack.two_diamond_card[index] << std::endl;
            break;
        }
    }

    // Roll for the 5th card
    double probabilities_fifth[] = {0.160, 0.888, 2.000, 10.288, 6.664, 20.000, 60.000};
    int fifth_roll_result = roll_special_die(probabilities_fifth);
    switch (fifth_roll_result) {
        case 1: {
            std::uniform_int_distribution<> dis(0, selected_pack.crown_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.crown_card[index]);
            std::cout << "God - " << selected_pack.crown_card[index] << std::endl;
            break;
        }
        case 2: {
            std::uniform_int_distribution<> dis(0, selected_pack.three_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.three_star_card[index]);
            std::cout << "Mythic - " << selected_pack.three_star_card[index] << std::endl;
            break;
        }
        case 3: {
            std::uniform_int_distribution<> dis(0, selected_pack.two_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.two_star_card[index]);
            std::cout << "Legendary - " << selected_pack.two_star_card[index] << std::endl;
            break;
        }
        case 4: {
            std::uniform_int_distribution<> dis(0, selected_pack.one_star_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.one_star_card[index]);
            std::cout << "Epic - " << selected_pack.one_star_card[index] << std::endl;
            break;
        }
        case 5: {
            std::uniform_int_distribution<> dis(0, selected_pack.four_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.four_diamond_card[index]);
            std::cout << "Ultra Rare - " << selected_pack.four_diamond_card[index] << std::endl;
            break;
        }
        case 6: {
            std::uniform_int_distribution<> dis(0, selected_pack.three_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.three_diamond_card[index]);
            std::cout << "Rare - " << selected_pack.three_diamond_card[index] << std::endl;
            break;
        }
        case 7: {
            std::uniform_int_distribution<> dis(0, selected_pack.two_diamond_card.size() - 1);
            int index = dis(gen);
            chosen_cards.push_back(selected_pack.two_diamond_card[index]);
            std::cout << "Uncommon - " << selected_pack.two_diamond_card[index] << std::endl;
            break;
        }
    }

    save_chosen_cards(chosen_cards);
}

// Main function to interact with the user
int main() {
    std::vector<Pack> packs = load_packs_from_file("packs.json");

    std::cout << "Welcome to the pack opening simulator!" << std::endl;
    std::cout << "How many packs would you like to open?" << std::endl;
    int num_packs;
    std::cin >> num_packs;

    std::cout << "Select a pack to open:" << std::endl;
    for (int i = 0; i < packs.size(); ++i) {
        std::cout << i + 1 << ". " << packs[i].name << std::endl;
    }

    int pack_choice;
    std::cin >> pack_choice;

    std::cout << "You have chosen the " << packs[pack_choice - 1].name << " pack!" << std::endl;
    std::cout << "\nYou pulled the following cards:" << std::endl;

    // Open the chosen pack the specified number of times
    for (int i = 0; i < num_packs; ++i) {
        open_pack(packs[pack_choice - 1]);
        std::cout << "------------------------" << std::endl;
    }

    std::cout << "\nThank you for opening packs! Check obtained_cards.txt for your results." << std::endl;
    return 0;
}
