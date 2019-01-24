// var pageavilable = [true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true];




function tabclick(e) {

    var tclass = e.currentTarget.className;
    var t;
    console.log(tclass)
    if (tclass == "tab active") return;
    else {
        let list = document.getElementsByTagName("li")
        let ilist = document.getElementsByTagName("iframe")
        for (i = 0; i < list.length - 1; i++) {
            if (list[i].className != "tab") list[i].className = "tab"
            if (list[i].className != "frame-hidden")ilist[i].className = "frame-hidden";
        }
        e.currentTarget.className = "tab  active";
        for (i = 0; i < list.length - 1; i++) {
            if (list[i].className == e.currentTarget.className) {
                t = i;
                console.log(t)
            }
        } 
        e.currentTarget.className = "tab  active";
        ilist[t].className = "old";
        let nnnnnnn=document.getElementsByTagName("input")[0];
        console.log(nnnnnnn,ilist[t].src)
        nnnnnnn.value=ilist[t].src;
    }

}
function tabaddclick(e) {

}
function tabcloseclick(e) {

}
function butbackclick(e) {

}
function butaheadclick(e) {

}
function butreclick(e) {

}
function butrepress(e) {

}
function butrewait(e) {

}
function starclick(e) {

}
function menuclick(e) {

}
function historyclick(e) {

}
var historyall = new Array(128);
var favor = [];
function monitor(e) {
    //     let ffff=document.getElementById(e.currentTarget.id);
    //     console.log(ffff)
    //     let fffffffff=ffff.contentWindow.document;
    //     console.log(fffffffff)
    //     let tittttt=fffffffff.getElementsByTagName("title");
    //     console.log(tittttt)
    //     var mulu = document.location.toString();
    //     mulu = mulu.slice(0, mulu.length - 10)
    //     console.log(mulu + "new.html")
    //     var tname = e.currentTarget.name
    //     var turl = e.currentTarget.src
    //     let urlist = turl.split('/')
    //     let urlnnn = urlist[0] + "//" + urlist[1] + "/" + urlist[2] + "/favicon.ico"
    //     console.log(urlnnn)
    //     console.log(tname, turl)
    //     if (tname != "new") {
    //         var num = parseInt(tname);
    //         if (pageavilable[num]) pageavilable[num] = false;
    //         historyall.push([tname, turl,urlnnn,])
    //     }
    //     else if (turl != mulu + "new.html") {

    //         for (let i = 0; i < pageavilable.length; i++)
    //             if (pageavilable[i]) {
    //                 e.currentTarget.name = "p" + i;
    //                 historyall.push(["p" + i, turl])
    //                 if (document.getElementsByClassName("tab-placeholder"))
    //                     favor.push([turl]);
    //                 else {
    //                     let tabadd = getElementsByClassName("tabs-add")
    //                     let tabnnn = createElement("li")
    //                     let tabimg = createElement("img")
    //                     let tabcon = createElement("div")
    //                     let tabclo = createElement("div")

    //                 }
    //                 return
    //             } alert("标签页过多！(too much pages)")
    //     } else return;

}



