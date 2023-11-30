import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    userProfile = db.execute("select Stock,Quantity,Price from stockprofile where user_id = ?", session["user_id"])
    stocksymbol = db.execute("select Stock from stockprofile where user_id = ?", session["user_id"])
    balance = usd(db.execute("select cash from users where id = ?", session["user_id"])[0].get("cash"))

    outputlist = []
    print("length of userProfile: ", len(userProfile))
    print(stocksymbol)
    #Use lookup to find the current price of the stock
    #print(lookup("NFLX"))
    marketprice = []
    if len(userProfile) > 0:
        for profile in userProfile:

            marketprice = lookup(profile["Stock"])

            output = {
                "Stock": profile["Stock"],
                "Quantity": profile["Quantity"],
                "Price": usd(profile["Price"]),
                "Market_Price": usd(marketprice["price"])
            }

            # print(k,v)
            print("output: ", output)
            outputlist.append(output)
            print("outputlist: ", outputlist)


        return render_template("index.html", outputlist = outputlist, balance = balance)
    else:

        outputlist = None

        return render_template("index.html", outputlist = outputlist, balance = balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("buy.html")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            #get user input
            stocksymbol = request.form.get("symbol")
            sharequantity = request.form.get("shares")
            print(stocksymbol)
            print(sharequantity)
            #check totalstock price
            stockprice = lookup(stocksymbol)["price"]
            print("Market price is: ", stockprice)

            #handle exception for invalid stock symbol
            if stockprice == None or "":
                return apology("There is no such stock")

            elif sharequantity.isnumeric() is False or int(sharequantity) <= 0:
                return apology("You must enter a positive number")

            elif(float((sharequantity)).is_integer() is False):
                return apology("You must enter a whole number")
        except:
            return apology("an unexpected error occured, please try again", 400)

        #handle purchase
        try:
            # check if the user has enough cash
            totalprice =  stockprice * int(sharequantity)
            cash = db.execute("select cash from users where id = ?", session["user_id"])
            print("totalprice: ", totalprice, type(totalprice))
            balance = cash[0]["cash"]
            print("balance: ", balance, type(balance))

            if balance < totalprice:
                return apology("You do not have enough cash")

            #log the transaction record into the database
            db.execute("insert into trade (user_id, Stock, Quantity, total_Bought) values (?,?,?,?);", session["user_id"], stocksymbol, sharequantity, totalprice)
            #update the cash balance of the user
            newbalance = balance - totalprice
            db.execute("update users set cash = ? where id = ?;", newbalance, session["user_id"])

            #update the stockprofile of the user
            #Get the total stock quantity & price to be updated
            Quantitylist = db.execute("select Quantity , Price from stockprofile where user_id = ? and Stock = ? ", session["user_id"], stocksymbol)

            #if the user already have this stock purchased, update it
            if (len(Quantitylist) > 0):
                for row in Quantitylist:
                    exQuantity = row["Quantity"]
                    exPrice = row["Price"]
                totalquantity = float(exQuantity) + float(sharequantity)
                newtotalprice = totalprice + exPrice
                db.execute("update stockprofile set Quantity = ? , Price = ? where user_id = ? and Stock = ?",int(totalquantity), newtotalprice, session["user_id"], stocksymbol)

            #if he do not have the stock purchased before, add it
            else:
                #Update the stock average price
                db.execute("insert into stockprofile (user_id, Stock, Quantity, Price) values (?,?,?,?) ",session["user_id"], stocksymbol,int(sharequantity), totalprice )

        except:
                return apology("an unexpected error occured, please try again", 400)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    #access the Database and get the row of data belong to the user
    #display it in the html
    historylist = db.execute("Select * from trade where user_id = ?", session["user_id"])
    print(historylist)

    if request.method == "GET":
        return render_template("history.html", historylist = historylist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Quote Stock"""
    if request.method =="GET" :
        #display form to request a stock quote
        return render_template("quote.html")
    if request.method == "POST":

        #get userinput
        stockname = request.form.get("symbol")
        stockquote = lookup(stockname)

        #handle exception
        if stockquote == None or "":
            return apology("Inbvalid stock name", 400)

        else:
            stockquote["price"] = usd(stockquote["price"])
            return render_template("quoted.html", stockquote = stockquote)

@app.route("/register", methods=["GET", "POST"])
def register():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("register.html")

   # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            #save username & password into a variable
            username = request.form.get("username")
            password = request.form.get("password")
            confirmation = request.form.get("confirmation")

            #check db to ensure theres no duplicate username
            dbUsername = db.execute("SELECT username FROM users WHERE username = ?", username)
            print(dbUsername)
            print(username)

            if username == "":
                return apology("You must enter username ", 400)
            elif password == "":
                return apology("You must enter password ", 400)
            elif confirmation == "":
                return apology("You must confirm password ", 400)
            elif password != confirmation:
                return apology("The password must match", 400)
            elif dbUsername != []:
                print("hello")
                print(dbUsername[0]["username"])
                if dbUsername[0]["username"] == username:
                    return apology("The username is already registered", 400)
            else:
                hash = generate_password_hash(password)
                #print(hash)
                db.execute("insert into users (username, hash) values (?,?);", username, hash)
            return redirect("/")

        except:
             return apology("an unexpected error occured, please try again", 400)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == ("GET"):
         return render_template("sell.html")
    if request.method == ("POST"):
        #Require user to input a stock symbol
        stocksymbol = request.form.get("symbol")
        sharequantity = request.form.get("shares")

        if lookup(stocksymbol) is None:
            return apology("Invalid stock name")

        elif(float((sharequantity)).is_integer() is False):
            return apology("You must enter a whole number")

        elif(db.execute("select Quantity from stockprofile where user_id = ?",  session["user_id"])[0].get("Quantity")) < int(sharequantity):
            return apology("You do not have enough share to sell")

        stockprice = lookup(stocksymbol)["price"]
        totalprice = int(sharequantity) * stockprice

        #Update the database
        #input a transaction record
        db.execute("insert into trade (user_id, Stock, Quantity, total_Sold) values (?,?,?,?);", session["user_id"], stocksymbol, sharequantity, totalprice)

        #update stockprofile
        newquantity = (db.execute("select Quantity from stockprofile where user_id = ?",session["user_id"])[0].get("Quantity")) - int(sharequantity)
        print("newquantity: " , newquantity)
        db.execute("update stockprofile set Quantity = ?, Price = ? where user_id = ? and Stock = ?", newquantity, totalprice, session["user_id"], stocksymbol)

        #update the balance
        balance = db.execute("select cash from users where id = ?",  session["user_id"])[0].get("cash")
        newbalance = float(balance) + float(totalprice)
        db.execute("update users set cash = ? where id = ?", newbalance, session["user_id"])

        #redirect to main page
        return redirect("/")
