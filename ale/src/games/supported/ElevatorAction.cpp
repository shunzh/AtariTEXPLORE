/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2012 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 */
#include "ElevatorAction.hpp"

#include "../RomUtils.hpp"


ElevatorActionSettings::ElevatorActionSettings() {

    reset();
}


/* create a new instance of the rom */
RomSettings* ElevatorActionSettings::clone() const { 
    
    RomSettings* rval = new ElevatorActionSettings();
    *rval = *this;
    return rval;
}


/* process the latest information from ALE */
void ElevatorActionSettings::step(const System& system) {

    // update the reward
    int score = getDecimalScore(0x89, 0x88, 0x87, &system);
    m_reward = score - m_score;
    m_score = score;

    // update terminal status
    int lives = readRam(&system, 0x83);
    int is_start_screen = readRam(&system, 0x81) == 0x00;
    m_terminal = lives == 0 && !is_start_screen;
}


/* is end of game */
bool ElevatorActionSettings::isTerminal() const {

    return m_terminal;
};


/* get the most recently observed reward */
reward_t ElevatorActionSettings::getReward() const { 

    return m_reward; 
}


/* is an action legal */
bool ElevatorActionSettings::isLegal(const Action &a) const {

    switch (a) {
        case PLAYER_A_NOOP:
        case PLAYER_A_RIGHT:
        case PLAYER_A_LEFT:
        case PLAYER_A_UP:
        case PLAYER_A_DOWN:
        case PLAYER_A_RIGHTFIRE:
        case PLAYER_A_LEFTFIRE:
        case PLAYER_A_UPFIRE:
        case PLAYER_A_DOWNFIRE:
        case PLAYER_A_FIRE:
            return true;
        default:
            return false;
    }   
}


/* reset the state of the game */
void ElevatorActionSettings::reset() {
    
    m_reward   = 0;
    m_score    = 0;
    m_terminal = false;
}

        
/* saves the state of the rom settings */
void ElevatorActionSettings::saveState(Serializer & ser) {
  ser.putInt(m_reward);
  ser.putInt(m_score);
  ser.putBool(m_terminal);
}

// loads the state of the rom settings
void ElevatorActionSettings::loadState(Deserializer & ser) {
  m_reward = ser.getInt();
  m_score = ser.getInt();
  m_terminal = ser.getBool();
}

