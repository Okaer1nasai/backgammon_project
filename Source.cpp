#include <algorithm>
#include <iostream>
#include <vector>

namespace ruslan {
    class Referee {
        std::pair<int, int> GetDices() {
            srand(6);
            std::pair<int, int> Dices;
            Dices.first = rand();
            Dices.second = rand();
            return Dices;
        }
    };

    class IStrategy {
    public:
        typedef std::vector<std::pair<int, int>> TMove;
        std::vector<TMove> GetGoodMoves(std::pair<int, int> Dices) {
            std::vector<TMove> result;
            if (Dices.first != Dices.second) {
                isfirst = false;
                std::vector<int> dicespread1(2);
                dicespread1[0] = Dices.first;
                dicespread1[1] = Dices.second;
                std::vector<int> dicespread2(2);
                dicespread2[0] = Dices.second;
                dicespread2[1] = Dices.first;
                if (iswhite) {
                    for (size_t i = 0; i < 18; ++i) {
                        std::vector<int> board_copy(Board);
                        TMove t;
                        if (!ishead(i) && board_copy[i] > 0) {
                            if (board_copy[i + dicespread1[0]] >= 0) {
                                t.push_back(std::make_pair(i, i + dicespread1[0]));
                                board_copy[i]--;
                                board_copy[i + dicespread1[0]]++;
                                for (size_t j = 0; j < 18; ++j) {
                                    if (!ishead(j) && board_copy[j] > 0) {
                                        if (board_copy[j + dicespread1[1]] >= 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread1[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                    if (ishead(j) && board_copy[j] > 0) {
                                        if (board_copy[j + dicespread1[1]] >= 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread1[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                }
                            }
                        }
                        if (ishead(i) && board_copy[i] > 0) {
                            if (board_copy[i + dicespread1[0]] >= 0) {
                                t.push_back(std::make_pair(i, i + dicespread1[0]));
                                board_copy[i]--;
                                board_copy[i + dicespread1[0]]++;
                                for (size_t j = 1; j < 18; ++j) {
                                    if (board_copy[j + dicespread1[1]] >= 0 && board_copy[j] > 0) {
                                        TMove t1(t);
                                        t1.push_back(std::make_pair(j, j + dicespread1[1]));
                                        result.push_back(t1);
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    for (size_t i = 12; i < 30; ++i) {
                        std::vector<int> board_copy(Board);
                        TMove t;
                        if (!ishead(i % 24) && board_copy[i % 24] < 0) {
                            if (board_copy[(i + dicespread1[0]) % 24] <= 0) {
                                t.push_back(std::make_pair(i % 24, (i + dicespread1[0]) % 24));
                                board_copy[i % 24]++;
                                board_copy[(i + dicespread1[0]) % 24]--;
                                for (size_t j = 12; j < 30; ++j) {
                                    if (!ishead(j % 24) && board_copy[j % 24] < 0) {
                                        if (board_copy[(j + dicespread1[1]) % 24] >= 0 && board_copy[j % 24] < 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j % 24, (j + dicespread1[1]) % 24));
                                            result.push_back(t1);
                                        }
                                    }
                                    if (ishead(j % 24) && board_copy[j % 24] < 0) {
                                        if (board_copy[(j + dicespread1[1]) % 24] <= 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread1[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                }
                            }
                        }
                        if (ishead(i % 24) && board_copy[i % 24] < 0) {
                            if (board_copy[(i + dicespread1[0]) % 24] <= 0) {
                                t.push_back(std::make_pair(i % 24, (i + dicespread1[0]) % 24));
                                board_copy[i % 24]++;
                                board_copy[(i + dicespread1[0])]--;
                                for (size_t j = 13; j < 30; ++j) {
                                    if (board_copy[(j + dicespread1[1]) % 24] <= 0 && board_copy[j % 24] < 0) {
                                        TMove t1(t);
                                        t1.push_back(std::make_pair(j % 24, (j + dicespread1[1]) % 24));
                                        result.push_back(t1);
                                    }
                                }
                            }
                        }
                    }
                }
                if (iswhite) {
                    iswhite = false;
                    for (size_t i = 0; i < 18; ++i) {
                        std::vector<int> board_copy(Board);
                        TMove t;
                        if (!ishead(i) && board_copy[i] > 0) {
                            if (board_copy[i + dicespread2[0]] >= 0) {
                                t.push_back(std::make_pair(i, i + dicespread2[0]));
                                board_copy[i]--;
                                board_copy[i + dicespread2[0]]++;
                                for (size_t j = 0; j < 18; ++j) {
                                    if (!ishead(j) && board_copy[j] > 0) {
                                        if (board_copy[j + dicespread2[1]] >= 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread2[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                    if (ishead(j) && board_copy[j % 24] > 0) {
                                        if (board_copy[j + dicespread2[1]] >= 0 && board_copy[j] > 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread2[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                }
                            }
                        }
                        if (ishead(i) && board_copy[i] > 0) {
                            if (board_copy[i + dicespread2[0]] >= 0) {
                                t.push_back(std::make_pair(i, i + dicespread2[0]));
                                board_copy[i]--;
                                board_copy[i + dicespread2[0]]++;
                                for (size_t j = 1; j < 18; ++j) {
                                    if (board_copy[j + dicespread2[1]] >= 0 && board_copy[j] > 0) {
                                        TMove t1(t);
                                        t1.push_back(std::make_pair(j, j + dicespread2[1]));
                                        result.push_back(t1);
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    iswhite = true;
                    for (size_t i = 12; i < 30; ++i) {
                        std::vector<int> board_copy(Board);
                        TMove t;
                        if (!ishead(i % 24) && board_copy[i % 24] < 0) {
                            if (board_copy[(i + dicespread2[0]) % 24] <= 0) {
                                t.push_back(std::make_pair(i % 24, (i + dicespread2[0]) % 24));
                                board_copy[i % 24]++;
                                board_copy[(i + dicespread2[0]) % 24]--;
                                for (size_t j = 12; j < 30; ++j) {
                                    if (!ishead(j % 24) && board_copy[j % 24] < 0) {
                                        if (board_copy[(j + dicespread2[1]) % 24] <= 0 && board_copy[j % 24] < 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j % 24, (j + dicespread2[1]) % 24));
                                            result.push_back(t1);
                                        }
                                    }
                                    if (ishead(j % 24) && board_copy[j % 24] < 0) {
                                        if (board_copy[(j + dicespread2[1]) % 24] <= 0) {
                                            TMove t1(t);
                                            t1.push_back(std::make_pair(j, j + dicespread2[1]));
                                            result.push_back(t1);
                                        }
                                    }
                                }
                            }
                        }
                        if (ishead(i % 24) && board_copy[i % 24] < 0) {
                            if (board_copy[(i + dicespread2[0]) % 24] <= 0) {
                                t.push_back(std::make_pair(i % 24, (i + dicespread2[0]) % 24));
                                board_copy[i % 24]++;
                                board_copy[(i + dicespread2[0])]--;
                                for (size_t j = 13; j < 30; ++j) {
                                    if (board_copy[(j + dicespread2[1]) % 24] <= 0 && board_copy[j % 24] < 0) {
                                        TMove t1(t);
                                        t1.push_back(std::make_pair(j % 24, (j + dicespread2[1]) % 24));
                                        result.push_back(t1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                std::vector<int> dicespread;
                dicespread.push_back(Dices.first);
                dicespread.push_back(Dices.first);
                dicespread.push_back(Dices.first);
                dicespread.push_back(Dices.first);

            }
            return result;
        }
    private:
        bool ishead(int i) {
            if (i == 0 || i == 12) {
                return true;
            }
            else
                return false;
        }
        std::vector<int> Board{ 14, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        bool isfirst = true;
        bool iswhite = true;
    };
}

int main() {
    ruslan::IStrategy player1;
    for (auto i : player1.GetGoodMoves(std::make_pair(5, 6))) {
        std::cout << '|';
        for (auto j : i)
            std::cout  << j.first << ' ' << j.second << ' ';
        std::cout << '|' << '\n';
    }
}
