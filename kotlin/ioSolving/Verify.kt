package ioSolving

fun checker(correct: String) {
    val my = OUTPUT.toString()
    if(my == correct) {
        println("Accepted")
    } else {
        println("Wrong Answer, Your Answer:\n $my")
    }
}