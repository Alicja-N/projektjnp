using std::string;
enum class rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
class Review{
public:
    enum Rank {
    };
    Rank rank;
    string text;
    string autor;
};