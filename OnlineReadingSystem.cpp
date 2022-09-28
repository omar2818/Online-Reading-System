#include <bits/stdc++.h>
#include <ctime>
using namespace std;

int readN(int low,int high){
    int value;
    cout<<"Enter number in range "<<low<<" "<<high<<" :";
    cin>>value;
    if(value>=low && value<=high){
        return value;
    }
    cout<<"invalid number please try again"<<endl;
    return readN(low,high);
}

int showmenu(const vector<string> choice){
    cout<<"Menu"<<endl;
    for(int i=0;i<choice.size();i++){
        cout<<i+1<<" : "<<choice[i]<<endl;
    }
    return readN(1,choice.size());
}

string get_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    cout<<ss.str();
    return ss.str();
}

vector<string> ReadFileLines(const string &path) {
	vector<string> lines;

	fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}

void WriteFileLines(const string &path, const vector<string> &lines, bool append = true) {
	auto status = ios::in | ios::out | ios::app;

	if (!append)
		status = ios::in | ios::out | ios::trunc;	// overwrite

	fstream file_handler(path.c_str(), status);

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return;
	}
	for (const auto &line : lines)
		file_handler << line << "\n";

	file_handler.close();
}

vector<string> SplitString(const string &str, const string &delimiter = ",") {
	string s = str;
	vector<string> strs;

	int pos = 0;
	string substr;
	while ((pos = (int) s.find(delimiter)) != -1) {
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimiter.length());
	}
	strs.push_back(s);
	return strs;
}

int ToInt(const string &str) {
	istringstream iss(str);
	int num;
	iss >> num;

	return num;
}

class Book{
    private:
        string bookname;
        string authorname;
        string bookid;
        int numberofpages;
        vector<string>pages;
        
    public:
        Book(const string &line) {
            vector<string> substrs = SplitString(line);
		    
            bookname=substrs[0];
            
            authorname=substrs[1];
            
            bookid=substrs[2];
            
            numberofpages = ToInt(substrs[3]);
            
            for(int pg=4;pg<substrs.size();pg++){
                pages.push_back(substrs[pg]);
            }

        }

        void Read() {
            string id,tit,nam,str;
            int s;

            cout << "Enter Title: ";
            cin >> tit;
            bookname=tit;

            cout << "Enter Author Name: ";
            cin >> nam;
            authorname=nam;
            
            cout << "Enter BookID: ";
            cin >> id;
            bookid=id;
            
            cout << "Enter How many pages: ";
            cin >> s;
            numberofpages=s;
            
            for (int page = 0; page < s; ++page) {
                cout << "Enter page # " << page + 1 << ": ";
                cin >> str;
                pages.push_back(str);
            }

        }

        const vector<string>& getpages() const {
            return pages;
        }

        void setpages(const vector<string>& pages) {
            this->pages = pages;
        }

        const int getnumberofpages()const{
            return numberofpages;
        }

        void setnumberofpages(const int& numberofpages){
            this->numberofpages=numberofpages;
        }

        const string& getbookid() const {
            return bookid;
        }

        void setbookid(const string& bookid) {
            this->bookid = bookid;
        }

        const string& getauthorname() const {
            return authorname;
        }

        void setauthorname(const string& authorname) {
            this->authorname = authorname;
        }

        const string& getbookname() const {
            return bookname;
        }

        void setbookname(const string& bookname) {
            this->bookname = bookname;
        }

        string tostring() {
            ostringstream oss;
            oss<<getbookname()<<","<<getauthorname()<<","<<getbookid()<<","<<getnumberofpages()<<",";
            for(int pg=0;pg<pages.size();pg++){
                oss<<pages[pg];
                if(pg!=pages.size()-1){
                    oss<<",";
                }
            }
            return oss.str();
        }

};

class Reading{
    private:
        Book* book;
        int current_page;
        string last_access;
    public:
        Reading(): Reading(nullptr){

        }

        Reading(Book* book): book(book), current_page(1), last_access(get_current_time_and_date()){

        }

        Reading(const string &line) {
            vector<string> substrs = SplitString(line);
		    
            last_access=substrs[1];

            current_page=ToInt(substrs[2]);

            string lin=tobook(substrs);
            Book* book=new Book(lin);
            book=book;
            
        }

        string tobook(vector<string> substrs){
            ostringstream oss;
            oss<<substrs[3]<<","<<substrs[4]<<","<<substrs[5]<<","<<substrs[6]<<",";
            for(int pg=7;pg<substrs.size();pg++){
                oss<<substrs[3];
                if(pg!=substrs.size()-1){
                    oss<<",";
                }
            }
            return oss.str();
        }

        string tostring(){
            ostringstream oss;
            oss<<last_access<<","<<book->tostring();
            return oss.str();
        }

        string View(){
            ostringstream oss;
            oss<<getbook()->getbookname()<<" Page: "<<PageIdxStr()<<" accessed in "<<getlast_access();
            return oss.str();
        }

        string getcurrentpagecontent(){
            return book->getpages()[current_page-1];
        }

        const Book* getbook() const{
            return book;
        }

        const string& getlast_access() const{
            return last_access;
        }

        void Resetlast_access(){
            last_access=get_current_time_and_date();
        }

        int getcurrent_page() const{
            return current_page;
        }

        void Nextpage(){
            if(current_page<book->getnumberofpages()){
                current_page++;
            }
        }

        void Previouspage(){
            if(current_page>1){
                current_page--;
            }
        }

        string PageIdxStr(){
            ostringstream oss;
            oss<<getcurrent_page()<<"/"<<book->getnumberofpages();
            return oss.str();
        }

};

class User{
    private:
        string username;
        string password;
        string name;
        string email;
        string phonenumper;
        bool is_admin=false;
        vector<Reading*> reading_sessions;
        
        void freeloadeddata(){
            for (auto &session : reading_sessions)
                delete session;

            reading_sessions.clear();
        }

    public:
        
        User(const string &line) {
            vector<string> substrs = SplitString(line);
		    username=substrs[0];
            password=substrs[1];
            name=substrs[2];
            email=substrs[3];
            phonenumper=substrs[4];
            is_admin = ToInt(substrs[5]);
        }

        ~User() {
            //cout << "Destructor User\n";
            
            freeloadeddata();
        }
        string saveuser() const{
            ostringstream oss;
            oss<<getusername()<<","<<getpassword()<<","<<getname()<<","<<getemail()<<","<<getphonenumper()<<",";
            if(getis_admin()){
                oss<<"1";
            }else{
                oss<<"0";
            }
            return oss.str();
        }

        string View() const {
            ostringstream oss;
            oss << "Name: " << name;
            if (getis_admin())
                oss << " | Admin";
            oss << "\n";
            oss << "Email: " << email << "\n";
            oss << "User name: " << username << "\n";
            oss << "Phone number: " << phonenumper << "\n";
            return oss.str();
        }
        void Read(string user_name) {
            username=user_name;
            string str,ph,pas,na,em;

            cout << "Enter password: ";
            cin >> pas;
            password=pas;

            cout << "Enter name: ";
            cin >> na;
            name=na;

            cout << "Enter email: ";
            cin >> em;
            email=em;

            cout << "Enter phone number: ";
            cin >> ph;
            phonenumper=ph;

            

        }

        const string& getphonenumper()const{
            return phonenumper;
        }

        void setphonenumper(const string& phonenumper){
            this->phonenumper=phonenumper;
        }


        const string& getemail()const{
            return email;
        }

        void setemail(const string& email){
            this->email=email;
        }

        const string& getname()const{
            return name;
        }

        void setname(const string& name){
            this->name=name;
        }

        const string& getpassword()const{
            return password;
        }

        void setpassword(const string& password){
            this->password=password;
        }

        const string& getusername()const{
            return username;
        }

        void setusername(const string& username){
            this->username=username;
        }

        void setis_admin(bool is_admin){
            this->is_admin=is_admin;
        }

        bool getis_admin() const{
            return is_admin;
        }

        const vector<Reading*>& getreading_sessions()const{
            return reading_sessions;
        }

        Reading* addreadingsesssion(Book* book){
            Reading* session =new Reading(book);
            UpdateDatabase(book);
            reading_sessions.push_back(session);
            return session;
        }

        void LoadDatabase() {
            //cout<<"UserManager: LoadDatabase\n";

            freeloadeddata();
            
            vector<string> lines = ReadFileLines("sessions.txt");
            for (const auto &line : lines) {
                Reading* read=new Reading(line);
                vector<string>substrs=SplitString(line);
                if(substrs[0]==getusername()){
                    reading_sessions.push_back(read);
                }
            }
        }
        
        void UpdateDatabase(Book* book) {
            string line = tostring(book);
            vector<string> lines(1, line);
            WriteFileLines("sessions.txt", lines);
        }

        string tostring(Book* book){
            Reading* session =new Reading(book);
            ostringstream oss;
            oss<<getusername()<<","<<session->tostring();
            return oss.str();
        }

};

class UserManager {
    private:
        User* current_user=nullptr;
        map<string,User*> username_map;

        void freeloadeddata(){
            for(auto user:username_map){
                delete user.second;
            }
            username_map.clear();
            current_user=nullptr;
        }

    public:
        UserManager(){

        }
        
        ~UserManager(){
            //cout<<"Destuctor: UserManager\n";
            freeloadeddata();
        }
        
        void LoadDatabase() {
            //cout<<"UserManager: LoadDatabase\n";

            freeloadeddata();
            
            vector<string> lines = ReadFileLines("users.txt");
            for (const auto &line : lines) {
                User* user=new User(line);
                username_map[user->getusername()] = user;
            }
        }

        void Accesssystem(){
            int ch=showmenu({"Login","Sign Up"});
            if(ch==1){
                DoLogin();
            }else{
                DoSignUp();
            }
        }

        void DoLogin() {
		LoadDatabase();

		while (true) {
			string user_name, pass;
			cout << "Enter user user_name & password: ";
			cin >> user_name >> pass;

			if (!username_map.count(user_name)) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			User* user_exist = username_map.find(user_name)->second;

			if (pass != user_exist->getpassword()) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			current_user = user_exist;
			break;
		}
	}
        
        void DoSignUp() {
            string user_name;
            while (true) {
                cout << "Enter user name. (No spaces): ";
                cin >> user_name;

                if (username_map.count(user_name))
                    cout << "Already used. Try again\n";
                else
                    break;
            }

            current_user->Read(user_name);
            UpdateDatabase(current_user);
            username_map[current_user->getusername()] = current_user;
        }
        
        void UpdateDatabase(const User* user) {
            string line = user->saveuser();
            vector<string> lines(1, line);
            WriteFileLines("users.txt", lines);
        }

        const User* getcurrent_user() const{
            return current_user;
        }

        Reading* addreadingsesssion(Book* book){
            return current_user->addreadingsesssion(book);
        }
};

class BookManager{
    private:
        map<string,Book*> id_book_map;
        
        void freeloadeddata() {
            for (auto pair : id_book_map) {
                delete pair.second;
            }
            id_book_map.clear();
        }

    public:
        BookManager(){

        }
        
        ~BookManager(){
            //cout<<"Destuctor: BookManager\n";
            freeloadeddata();
        }

        void AddBook(Book* book){
            UpdateDatabase(book);
            id_book_map[book->getbookid()]=book;
        }

        Book* getbook(string id){
            return id_book_map[id];
        }

        void setid_book_map(const map<string,Book*>& id_book_map){
            this->id_book_map=id_book_map;
        }

        const map<string,Book*>& getid_book_map() const{
            return id_book_map;
        }

        void LoadDatabase() {
            //cout<<"BookManager: LoadDatabase\n";

            freeloadeddata();
            
            vector<string> lines = ReadFileLines("books.txt");
            for (const auto &line : lines) {
                Book* book=new Book(line);
                id_book_map[book->getbookid()] = book;
            }
        }

        void UpdateDatabase(Book* book) {
            string line = book->tostring();
            vector<string> lines(1, line);
            WriteFileLines("books.txt", lines);
        }


};

class UserView {
    private:
        UserManager &user_manager;
        BookManager &book_manager;
    public:
        UserView(UserManager &user_manager,BookManager &book_manager):user_manager(user_manager),book_manager(book_manager){

        }
        void Display(){
            const User* user=user_manager.getcurrent_user();

            cout<<"\n Hello "<<user->getusername();
            cout<<" | User View \n";

            vector<string>menu;
            menu.push_back("View Profile");
            menu.push_back("List & Select from My Reading History");
            menu.push_back("List & Select from Available Books");
            menu.push_back("Logout");
            
            while (1)
            {
                int choise=showmenu(menu);
                if(choise==1){
                    Viewprofile();
                }else if(choise==2){
                    listreadinghistory();
                }else if(choise==3){
                    listavailableBooks();
                }else{
                    break;
                }
            }
            
        }

        void Viewprofile(){
            const User* user=user_manager.getcurrent_user();

            cout<<"\n"<<user->View()<<"\n";
        }

        void Displaysession(Reading* session){
            vector<string> menu;
            menu.push_back("Next Page");
            menu.push_back("Previous Page");
            menu.push_back("Stop Reading");
            
            while (1)
            {
                cout<<"Current Page: "<<session->PageIdxStr()<<"\n";
                cout<<session->getcurrentpagecontent()<<"\n";

                int choice=showmenu(menu);
                if(choice==1){
                    session->Nextpage();
                }else if(choice==2){
                    session->Previouspage();
                }else{
                    break;
                }
            }
            session->Resetlast_access();
        }

        void listreadinghistory(){
            int idx=0;
            const auto& sessions=user_manager.getcurrent_user()->getreading_sessions();
            for(auto& session:sessions){
                idx++;
                cout<<idx<<" : "<<session->View()<<"\n";
            }
            if(idx==0){
                cout<<"\n No history \n";
            }else{
                cout<<"\n Which session to open? ";
                int choice=readN(1,idx);
                Displaysession(sessions[choice-1]);
            }
        }
        
        void listavailableBooks(){
            const map<string,Book*>& mp=book_manager.getid_book_map();

            cout<<"\n our current Books: \n";
            int idx=0;
            for(const auto &pair : mp){
                idx++;
                cout<<idx<<" "<<pair.second->getbookname()<<"\n";
            }
            cout<<"\n Which book to read? ";
            int choice=readN(1,idx);
            
            idx=1;
            for(const auto &pair : mp){
                if(idx==choice){
                    Reading* session=user_manager.addreadingsesssion(pair.second);
                    Displaysession(session);
                    break;
                }
                idx++;
            }
        }
};

class AdminView {
    private:
        UserManager &user_manager;
        BookManager &book_manager;
    public:
        AdminView(UserManager &user_manager,BookManager &book_manager):user_manager(user_manager),book_manager(book_manager){

        }

        void Display(){
            const User* user=user_manager.getcurrent_user();

            cout<<"\n Hello "<<user->getusername();
            cout<<" | Admin View \n";

            vector<string>menu;
            menu.push_back("View Profile");
            menu.push_back("Add Book");
            menu.push_back("Logout");
            
            while (1)
            {
                int choise=showmenu(menu);
                if(choise==1){
                    Viewprofile();
                }else if(choise==2){
                    AddBook();
                }else{
                    break;
                }
            }
            
        }

        void Viewprofile(){
            const User* user=user_manager.getcurrent_user();

            cout<<"\n"<<user->View()<<"\n";
        }

        void AddBook(){
            Book *book;
            book->Read();
            book_manager.AddBook(book);
        }
};

class onlinesystem{
    private:
        BookManager *book_manager;
        UserManager *user_manager;

        void loadDatabase(){
            book_manager->LoadDatabase();
            user_manager->LoadDatabase();
        }

    public:
        onlinesystem():book_manager(new BookManager()),user_manager(new UserManager()){

        }

        ~onlinesystem(){
            cout<<"Destructor: system \n";

            if(book_manager!=nullptr){
                delete book_manager;
                book_manager=nullptr;
            }

            if(user_manager!=nullptr){
                delete user_manager;
                user_manager=nullptr;
            }
        }

        void Run(){
            loadDatabase();

            while (1)
            {
                user_manager->Accesssystem();
                
                if(user_manager->getcurrent_user()->getis_admin()){
                    AdminView view(*user_manager,*book_manager);
                    view.Display();
                }else{
                    UserView view(*user_manager,*book_manager);
                    view.Display();
                }

            }
            
        }

};

int main(){
    onlinesystem site;
    site.Run();
    return 0;
}