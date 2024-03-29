#include "RequestHandlers.h"

LoginHandler::LoginHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

SignUpHandler::SignUpHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

LogoutHandler::LogoutHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

SubmitFilm::SubmitFilm(ProcessHandler* _handler)
{
    handler = _handler;
}

Profile::Profile(ProcessHandler* _handler)
{
    handler = _handler;
}

Home::Home(ProcessHandler* _handler)
{
    handler = _handler;
}

MovieDetails::MovieDetails(ProcessHandler* _handler)
{
    handler = _handler;
}

Response* LoginHandler::callback(Request* req)
{
    try
    {
        Map loginInput = {{"username",""},{"password",""}};
        loginInput["username"] = req->getBodyParam("username");
        loginInput["password"] = req->getBodyParam("password");
        handler->checkInput(loginInput,"login");
        std::string session_id = handler->login(loginInput,"login");
        Response* res = Response::redirect("/home");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        res->setSessionId(session_id);
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}

Response* SignUpHandler::callback(Request* req)
{
    try
    {
        Map signUpInput = {{"email",""},{"username",""},
            {"password",""},{"age",""},{"is_publisher",""}};
        signUpInput["username"] = req->getBodyParam("username");
        signUpInput["password"] = req->getBodyParam("password");
        signUpInput["email"] = req->getBodyParam("email");
        signUpInput["age"] = req->getBodyParam("age");
        signUpInput["is_publisher"] = req->getBodyParam("is_publisher");
        handler->checkInput(signUpInput,"signup");
        std::string session_id = handler->signup(signUpInput,"signup");
        Response* res = Response::redirect("/home");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        res->setSessionId(session_id);
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}

Response* LogoutHandler::callback(Request* req)
{
    try
    {
        std::string req_session = req->getSessionId();
        handler->logout(req_session);
        Response* res = Response::redirect("/");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        res->setSessionId("");
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}

Response* SubmitFilm::callback(Request* req)
{
    try
    {
        std::string req_session = req->getSessionId();
        Map submissionInput = {{"name",""},{"year",""},{"length",""},
            {"price",""},{"summary",""},{"director",""}};
        submissionInput["name"] = req->getBodyParam("name");
        submissionInput["year"] = req->getBodyParam("year");
        submissionInput["length"] = req->getBodyParam("length");
        submissionInput["price"] = req->getBodyParam("price");
        submissionInput["summary"] = req->getBodyParam("summary");
        submissionInput["director"] = req->getBodyParam("director");
        handler->checkInput(submissionInput,"submitMovie");
        handler->submitMovie(submissionInput,req_session);
        Response* res = Response::redirect("/submitsuccess");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}

Response* Profile::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type","text/html");
    res->setHeader("Developer-Name","ariyan");
    try
    {
        Map input = {{"director",""}};
        std::vector<Movie*> purchases;
        std::string session_id = req->getSessionId(), body = "";
        input["director"] = req->getQueryParam("director");
        Map MoneyInput = {{"amount",""}};
        MoneyInput["amount"] = req->getQueryParam("amount");
        if(MoneyInput["amount"] != "")
            handler->chargeAccount(MoneyInput,session_id);
        purchases = handler->viewPurchases(input,session_id);
        body += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css\">";
        body += "<!DOCTYPE html>";
        body += "<html>";
        body += "<body style=\"background-image: url(/back.jpg); background-attachment: fixed; background-position : center ;\">";
        body += "<nav class=\"navbar navbar-inverse\"><div class=\"container-fluid\"><div class=\"navbar-header\">";
        body += "<img class=\"navbar-brand\" src=\"University_of_Tehran_logo.svg.png\" style=\"width: 60px; height : 60px;\"></a></div>";
        body += "<ul class=\"nav navbar-nav\"><li><a href=\"/submitfilm\">Add Movie</a></li>";
        body += "<li><a href=\"/moviedetails\">Find Movies</a></li></ul>";
        body += "<ul class=\"nav navbar-nav navbar-right\">";
        body += "<li></li><li><a href = \"/home\">Home</li><li><a href=\"/logout\">";
        body += "<span class=\"glyphicon glyphicon-log-out\"></span>Log out</a></li></ul></ul></div></nav>";
        body += "<div align = \"center\"><form action = \"/profile\" method = \"GET\" style = \"width: 50%;\">";
        body += "<h4 style = \"color:white;\">Charge Your Account</h4><br>";
        body += "<p style = \"color:white;\">Amount :  </p>";
        body += "<input type = \"text\" name = \"amount\">";
        body += "<input type = \"submit\" value = \"Charge\" ><br><br>";
        body += "<h4 style = \"color:white;\">$ = ";
        std::string money = handler->viewMoney(input,session_id);
        body += money;
        body += "</h4></div></form>";
        body += "<div align = \"center\"><br><h3 style = \"color:white;\">Purchased Movies<h3></div>";
        body += "<table class=\"table table-striped\" align = \"center\" style = \"width:75%; background-color : rgb(23, 48, 80);color : yellow;\">";
        body += "<style> th {color : gray; background-color : rgb(23, 48, 80); }</style>";
        body += "<tr><th>Index</th><th>Name</th><th>Year</th>";
        body += "<th>Length</th><th>Price</th><th>Rate</th><th>Director</th></tr>";
        for(Counter i=0; i<purchases.size(); i++)
        {
            body += "<tr><td>";
            body += std::to_string(i+1);
            body += "</td><td>";
            body += purchases[i]->getName();
            body += "</td><td>";
            body += std::to_string(purchases[i]->getYear());
            body += "</td><td>";
            body += std::to_string(purchases[i]->getLength());
            body += "</td><td>";
            body += std::to_string(purchases[i]->getPrice());
            body += "</td><td>";
            body += std::to_string(purchases[i]->getRate());
            body += "</td><td>";
            body += purchases[i]->getDirector();
            body += "</td></tr>";
        }
        body += "</table><div align = \"center\"><form action = \"/profile\" method = \"GET\">";
        body += "<input type = \"text\" name = \"director\" value = \"Enter a Director's Name\"><br>";
        body += "<input type = \"submit\" value = \"Filter\" ></form></div><br>";
        body += "</body>";
        body += "</html>";
        res->setBody(body);
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
    return res;
}

Response* Home::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type","text/html");
    res->setHeader("Developer-Name","ariyan");
    try
    {
        std::string session_id = req->getSessionId(), body = "", Delete = "";
        body += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css\">";
        body += "<!DOCTYPE html>";
        body += "<html>";
        body += "<body style=\"background-image: url(/back.jpg); background-attachment: fixed; background-position : center;\">";
        body += "<nav class=\"navbar navbar-inverse\"><div class=\"container-fluid\"><div class=\"navbar-header\">";
        body += "<img class=\"navbar-brand\" src=\"University_of_Tehran_logo.svg.png\" style=\"width: 60px; height : 60px;\"></a></div>";
        body += "<ul class=\"nav navbar-nav\"><li><a href=\"/submitfilm\">Add Movie</a></li>";
        body += "<li><a href=\"/moviedetails\">Find Movies</a></li></ul>";
        body += "<ul class=\"nav navbar-nav navbar-right\">";
        body += "<li><a href = \"/profile\">Profile</li><li><a href=\"/logout\">";
        body += "<span class=\"glyphicon glyphicon-log-out\"></span>Log out</a></li></ul></ul></div></nav>";
        if(handler->isPublisher(session_id) == true)
        {
            Map input = {{"director",""}}, deleteInput = {{"film_id",""}};
            input["director"] = req->getQueryParam("director");
            std::vector<Movie*> publishes;
            publishes = handler->viewPublishes(input,session_id);
            for(Counter i=0; i<publishes.size(); i++)
                if(req->getQueryParam(std::to_string(publishes[i]->getId())) == "delete")
                    Delete = std::to_string(publishes[i]->getId());
            if(Delete != "")
            {
                deleteInput["film_id"] = Delete;
                handler->deleteFilm(deleteInput,session_id);
                Delete = "";
            }
            publishes = handler->viewPublishes(input,session_id);
            body += "<div align = \"center\"><br><h3 style = \"color : white;\">Published Movies<h3></div>";
            body += "<table class=\"table table-striped\" align = \"center\" style = \"width:75%; background-color : rgb(23, 48, 80);color : yellow;\">";
            body += "<style> th {color : gray; background-color : rgb(23, 48, 80); }</style>";
            body += "<tr><th>Index</th><th>Name</th><th>Year</th>";
            body += "<th>Length</th><th>Price</th><th>Rate</th><th>Director</th><th>Details</th><th>Delete</th></tr>";
            for(Counter i=0; i<publishes.size(); i++)
            {
                body += "<tr><td>";
                body += std::to_string(i+1);
                body += "</td><td>";
                body += publishes[i]->getName();
                body += "</td><td>";
                body += std::to_string(publishes[i]->getYear());
                body += "</td><td>";
                body += std::to_string(publishes[i]->getLength());
                body += "</td><td>";
                body += std::to_string(publishes[i]->getPrice());
                body += "</td><td>";
                body += std::to_string(publishes[i]->getRate());
                body += "</td><td>";
                body += publishes[i]->getDirector();
                body += "</td><td>";
                body += "<a href = /moviedetails?film_id=";
                body += std::to_string(publishes[i]->getId());
                body += "&search=Search><span class=\"glyphicon glyphicon-info-sign\"></span></a>";
                body += "</td><td>";
                body += "<form action = \"/home\" method = \"GET\">";
                body += "<button type = \"submit\" value = \"delete\" style = \"background-color : rgb(23, 48, 80);\" name = \"";
                body += std::to_string(publishes[i]->getId());
                body += "\"><span class=\"glyphicon glyphicon-trash\" style = \"background-color : rgb(23, 48, 80);\"></span></button>";
                body += "</form></td></tr>";
            }
            body += "</table>";
            body += "<div align = \"center\"><form action = \"/home\" method = \"GET\">";
            body += "<input type = \"text\" name = \"director\" value = \"Enter a Director's Name\"><br>";
            body += "<input type = \"submit\" value = \"Filter\" ></form></div>";
        }
        std::vector<Movie*> movies;
        movies = handler->showValidMovies(session_id);
        if(handler->isPublisher(session_id) == false || movies.size() > 0)
        {
            body += "<div align = \"center\"><br><h3 style = \"color : white;\">Available Movies</h3></div>";
            body += "<table class=\"table table-striped\" align = \"center\" style = \"width:75%; background-color : rgb(23, 48, 80);color : yellow;\">";
            body += "<style> th {color : gray; background-color : rgb(23, 48, 80); }</style>";
            body += "<tr><th>Index</th><th>Name</th><th>Year</th>";
            body += "<th>Length</th><th>Price</th><th>Rate</th><th>Director</th><th>Details</th></tr>";
            for(Counter i=0; i<movies.size(); i++)
            {
                body += "<tr><td>";
                body += std::to_string(i+1);
                body += "</td><td>";
                body += movies[i]->getName();
                body += "</td><td>";
                body += std::to_string(movies[i]->getYear());
                body += "</td><td>";
                body += std::to_string(movies[i]->getLength());
                body += "</td><td>";
                body += std::to_string(movies[i]->getPrice());
                body += "</td><td>";
                body += std::to_string(movies[i]->getRate());
                body += "</td><td>";
                body += movies[i]->getDirector();
                body += "</td><td>";
                body += "<a href = /moviedetails?film_id=";
                body += std::to_string(movies[i]->getId());
                body += "&search=Search><span class=\"glyphicon glyphicon-info-sign\"></span></a>";
                body += "</td></tr>";
            }
            body += "</table>";
            body += "</body>";
            body += "</html>";
        }
        res->setBody(body);
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
    return res;
}

Response* MovieDetails::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type","text/html");
    res->setHeader("Developer-Name","ariyan");
    try
    {
        Movie* movie = NULL;
        std::string session_id = req->getSessionId(), body = "", buy = "";
        Map input = {{"film_id",""}}, rateInput = {{"film_id",""},{"score",""}},
            buyInput = {{"film_id",""}}, commentInput = {{"film_id",""},{"content",""}};
        rateInput["score"] = req->getQueryParam("score");
        input["film_id"] = req->getQueryParam("film_id");
        commentInput["content"] = req->getQueryParam("content");
        if(input["film_id"] != "")
            handler->setMovieId(stoi(input["film_id"]));
        buy = req->getQueryParam("Buy");
        if(input["film_id"] != "")
            movie = handler->searchMovie(stoi(input["film_id"]),session_id);
        if(buy == "Buy")
        {
            buyInput["film_id"] = std::to_string(handler->getLastId());
            handler->buy(buyInput,session_id);
            buy = "";
        }
        if(rateInput["score"] != "")
        {
            rateInput["film_id"] = std::to_string(handler->getLastId());
            handler->rateMovie(rateInput,session_id);
            rateInput["score"] = "";
        }
        if(commentInput["content"] != "")
        {
            commentInput["film_id"] = std::to_string(handler->getLastId());
            handler->postComment(commentInput,session_id);
            commentInput["content"] = "";
        }
        body += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css\">";
        body += "<!DOCTYPE html>";
        body += "<html>";
        body += "<body style=\"background-image: url(/back.jpg); background-attachment: fixed; background-position : center;\">";
        body += "<nav class=\"navbar navbar-inverse\"><div class=\"container-fluid\"><div class=\"navbar-header\">";
        body += "<img class=\"navbar-brand\" src=\"University_of_Tehran_logo.svg.png\" style=\"width: 60px; height : 60px;\"></a></div>";
        body += "<ul class=\"nav navbar-nav\"><li><a href=\"/submitfilm\">Add Movie</a></li>";
        body += "<li><a href=\"/home\">Home</a></li></ul>";
        body += "<ul class=\"nav navbar-nav navbar-right\">";
        body += "<li><a href = \"/profile\">Profile</li><li><a href=\"/logout\">";
        body += "<span class=\"glyphicon glyphicon-log-out\"></span>Log out</a></li></ul></ul></div></nav>";
        body += "<div align = \"center\"><form action = \"/moviedetails\" method = \"GET\" style = \"width: 50%;\">";
        body += "<h4 style = \"color : white;\">Type a Movie ID</h4><br>";
        body += "<form method = \"GET\" action = \"/moviedetails\">";
        body += "<input type = \"text\" name = \"film_id\"><br><br>";
        body += "<button type = submit name = \"search\" style = \"background-color : rgb(23, 48, 80);\" value = \"Search\">";
        body += "<span class=\"glyphicon glyphicon-search\" style = \"color : yellow;\"></span></button>";
        body += "</form></div>";
        if(movie != NULL)
        {
            body += "<div align = \"center\"><div style = \" border: 2px solid yellow; background-color : rgb(23, 48, 80); border-radius: 5px; width : 25%;\"><h4 style = \"color : white;\">Name : ";
            body += movie->getName();
            body += "<br><br>Length : ";
            body += std::to_string(movie->getLength());
            body += "<br><br>Price : ";
            body += std::to_string(movie->getPrice());
            body += "<br><br>Rate : ";
            body += std::to_string(movie->getRate());
            body += "<br><br>Length : ";
            body += std::to_string(movie->getLength());
            body += "<br><br>Year : ";
            body += std::to_string(movie->getYear());
            body += "<br><br>Director : ";
            body += movie->getDirector();
            body += "<br><br>Summary : ";
            body += movie->getSummary();
            body += "</h4></div><div><br>";
            if(handler->compareMoney(session_id,movie->getPrice()) == true
            && handler->hasPurchased(session_id,movie->getId()) == false)
            {
                body += "<div align = \"center\"><form action = \"/moviedetails?film_id=";
                body += std::to_string(movie->getId());
                body += "&search=Search\" method = \"GET\">";
                body += "<input type = \"submit\" value = \"Buy\" name = \"Buy\">";
                body += "</form></div>";
            }
            if(handler->hasPurchased(session_id,movie->getId()) == true)
            {
                body += "<div align =\"center\"><h4 style = \"color : yellow;\">Rate the Movie</h4><br><form action = \"/moviedetails?film_id=";
                body += std::to_string(movie->getId());
                body += "&search=Search\" method = \"GET\">";
                body += "<input type = \"text\" name = \"score\">";
                body += "<input type = \"submit\" value = \"Rate\"></form><br>";
                body += "<h4 style = \"color : yellow;\">Post a Comment</h4><br><form action = \"/moviedetails?film_id=";
                body += std::to_string(movie->getId());
                body += "&search=Search\" method = \"GET\">";
                body += "<input type = \"text\" name = \"content\">";
                body += "<input type = \"submit\" value = \"Post\" name = \"Post\">";
                body += "</form></div><br>";
            }
            std::vector<Comment*> comments = handler->viewComments(handler->getLastId(),session_id);
            if(comments.size() > 0)
            {
                body += "<div align = \"center\"><h3 style = \"color : yellow;\">Comments</h3>";
                body += "<table class=\"table table-striped\" align = \"center\" style = \"width:75%; background-color : rgb(23, 48, 80);color : yellow;\">";
                body += "<style> th {color : gray; background-color : rgb(23, 48, 80); }</style>";
                body += "<tr><th>Index</th><th>User ID</th><th>Comment</th>";
                for(Counter i=0; i<comments.size(); i++)
                {
                    body += "<tr><td>";
                    body += std::to_string(i+1);
                    body += "</td><td>";
                    body += std::to_string(comments[i]->getUserId());
                    body += "</td><td>";
                    body += comments[i]->getContent();
                    body += "</td></tr>";
                }
                body += "</table></div><br>";
            }
            std::vector<Movie*> recommends;
            recommends = handler->viewDetails(input,session_id);
            body += "<div align = \"center\"><h3 style = \"color : yellow;\">Recommended Movies</h3>";
            body += "<table class=\"table table-striped\" align = \"center\" style = \"width:75%; background-color : rgb(23, 48, 80);color : yellow;\">";
            body += "<style> th {color : gray; background-color : rgb(23, 48, 80); }</style>";
            body += "<tr><th>Index</th><th>Name</th><th>Year</th>";
            body += "<th>Length</th><th>Price</th><th>Rate</th><th>Director</th></tr>";
            for(Counter i=0; i<recommends.size(); i++)
            {
                body += "<tr><td>";
                body += std::to_string(i+1);
                body += "</td><td>";
                body += recommends[i]->getName();
                body += "</td><td>";
                body += std::to_string(recommends[i]->getYear());
                body += "</td><td>";
                body += std::to_string(recommends[i]->getLength());
                body += "</td><td>";
                body += std::to_string(recommends[i]->getPrice());
                body += "</td><td>";
                body += std::to_string(recommends[i]->getRate());
                body += "</td><td>";
                body += recommends[i]->getDirector();
                body += "</td><td>";
                body += "<a href = /moviedetails?film_id=";
                body += std::to_string(movie->getId());
                body += "&search=Search>Details</a>";
                body += "</td></tr>";
            }
            body += "</table></div>";
        }
        body += "</body>";
        body += "</html>";
        res->setBody(body);
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}