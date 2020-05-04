#include <iostream>

using namespace std;
const int ASCII_zero = 48 ;

struct MapPoint {

  int X ;
  int Y ;

  bool wall ; // can't pass this ;
  bool gold ;
  bool trap ; // warn player when player is near the trap point,
              // -> let player back to before point ;
  bool arrived ; // it means the player had arrived this point before ;

} ; // MapPoint
    // Information of the point ;

MapPoint map[100][100] ;
void StartGame( int sX, int sY, int & getGold ) ;
bool DetectTrap( int nowX, int nowY ) ;

int main() {

  cout << "Q5." << endl ;

  bool run = true ;
  while ( run ) {

    int playerX = 0 ;
    int playerY = 0 ;
    string input ;
    int mapWord = 0 ; // W
    int mapHigh = 0 ; // M
    bool WordStrat = false ;
    bool WordReadFinish = false ;

    cin >> mapWord ;
    cin >> mapHigh ;

    if ( mapWord == 0 && mapHigh == 0 )
      break ; // Done ;

    // MapPoint map[mapWord][mapHigh] ;
    input = "" ; // string clear ;
    for ( int i = 0 ; i < mapHigh ; i++ ) {
      cin >> input ;

      for ( int j = 0 ; j < mapWord ; j++ ) {

        MapPoint temp ;
        temp.X = j ;
        temp.Y = i ;
        temp.gold = false ;
        temp.trap = false ;
        temp.wall = false ;
        temp.arrived = false ;

        if ( input.at(j) == '#' )
          temp.wall = true ;
        else if ( input.at(j) == 'G' )
          temp.gold = true ;
        else if ( input.at(j) == 'T' )
          temp.trap = true ;
        else if ( input.at(j) == 'P' ) {
          playerX = j ;
          playerY = i ;
        } // else if

        map[j][i] = temp ;

      } // for

    } // for

    int getGold = 0 ;
    StartGame( playerX, playerY, getGold ) ;
    cout << "Gold:" << getGold << endl ;

  } // while

} // main()

void StartGame( int sX, int sY, int & getGold ) {

  // cout comment is showing the information of each move ;
  // cout << endl ;
  // cout << "X" << sX+1 << "Y" << sY+1 ;

  if ( !map[sX][sY].arrived && map[sX][sY].gold ) {
    getGold = getGold + 1 ;
    // cout << "GetGold, Now have " << getGold << " Golds" ;
  } // if

  map[sX][sY].arrived = true ;

  if ( !DetectTrap( sX, sY ) ) {
    // player near trap ;
    // back to the before point ;

    if ( !map[sX+1][sY].wall && !map[sX+1][sY].arrived )
      StartGame( sX+1, sY, getGold ) ;

    if ( !map[sX][sY+1].wall && !map[sX][sY+1].arrived )
      StartGame( sX, sY+1, getGold ) ;

    if ( !map[sX-1][sY].wall && !map[sX-1][sY].arrived )
      StartGame( sX-1, sY, getGold ) ;

    if ( !map[sX][sY-1].wall && !map[sX][sY-1].arrived )
      StartGame( sX, sY-1, getGold ) ;

  } // if
  // else
    // cout << "near trap" ;


} // StartGame()

bool DetectTrap( int nowX, int nowY ) {
  // true = have trap near this point ;
  // false = safe ;

  if ( map[nowX+1][nowY].trap )
    return true ;
  else if ( map[nowX][nowY+1].trap )
    return true ;
  else if ( map[nowX-1][nowY].trap )
    return true ;
  else if ( map[nowX][nowY-1].trap )
    return true ;
  else
    return false ;

} // DetectTrap()
