#!/bin/sh

# Fumes is a client implementation for Liquid War 7.
# Copyright (C)  2015  Christian Mauduit <ufoot@ufoot.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Fumes homepage: https://github.com/ufoot/fumes
# Contact author: ufoot@ufoot.org

if [ -d ../.utils ] ; then
    cd ..
fi
if [ ! -d .utils ] ; then
    echo "$0 should be run in srcdir"
    exit 1
fi

PACKAGE_TARNAME="fumes"
PACKAGE_NAME="Fumes Client"
PACKAGE_EMAIL="ufoot@ufoot.org"
PACKAGE_URL="http:\\/\\/www.ufoot.org\\/liquidwar\\/v7\\/fumes"
VERSION_MAJOR=0
VERSION_MINOR=1

find_configure_ac () {
    if [ -f configure.ac ] ; then
	    CONFIGURE_AC="configure.ac"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${CONFIGURE_AC}"
            exit 2
	    fi
    else
	    echo "unable to find configure.ac"
	    exit 1
    fi
}

find_fmversion_cpp () {
    if [ -f src/fmbuild/fmversion.cpp ] ; then
	    FMVERSION_CPP="src/fmbuild/fmversion.cpp"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${FMVERSION_CPP}"
            exit 2
	    fi
    else
	    echo "unable to find src/fmbuild/fmversion.cpp"
	    exit 1
    fi
}

find_fmpackage_cpp () {
    if [ -f src/fmbuild/fmpackage.cpp ] ; then
	    FMPACKAGE_CPP="src/fmbuild/fmpackage.cpp"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${FMPACKAGE_CPP}"
            exit 2
	    fi
    else
	    echo "unable to find src/fmbuild/fmpackage.cpp"
	    exit 1
    fi
}

git_check () {
    if git status > /dev/null 2>&1 ; then
        true
    else
        echo "this is not a git repo, $0 won't do anything"
        exit 0
    fi
}

git_changelog () {
    if which git2cl > /dev/null ; then
        GIT_FILES=$(ls -d * | grep -v "ChangeLog" | sort | tr "\n" " ")
        git log --pretty --numstat --summary -- $GIT_FILES | git2cl > ChangeLog
    fi
}

calc_branch () {
    VERSION_BRANCH=$(git branch --color=never | grep "* " | cut -c 3- | sed "s/ //g")
    if [ "x${VERSION_BRANCH}" = "x" ] ; then
        VERSION_BRANCH=unknown
    fi
    if [ "x${VERSION_BRANCH}" = "xmaster" ] ; then
        VERSION_BRANCH=
    fi
}

calc_commits () {
    if [ "x${VERSION_BRANCH}" = "x" ] ; then
	SRC_GO=$(ls -d fm* | grep -v "fmbuild" | sort | tr "\n" " ")
	VERSION_COMMITS=$(git log --oneline --color=never -- ${SRC_GO} | wc -l)
    else
	VERSION_COMMITS=
    fi
}

do_patch () {
    VERSION_STAMP=${VERSION_COMMITS}${VERSION_BRANCH}
    VERSION_DOT=${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STAMP}
    if grep -q ${VERSION_DOT} ${CONFIGURE_AC} ; then
        echo "current version is ${VERSION_DOT}"
        touch ${CONFIGURE_AC}
    else
        echo "patching ${FMPACKAGE_CPP} with package tarname=${PACKAGE_TARNAME} name=${PACKAGE_NAME} email=${PACKAGE_EMAIL} url=${PACKAGE_URL}"
        sed -i "s/constexpr.*\/\/.*PACKAGE_TARNAME.*stamp.sh/constexpr char *PACKAGE_TARNAME = \"${PACKAGE_TARNAME}\"; \/\/ PACKAGE_TARNAME set by stamp.sh/g" ${FMPACKAGE_CPP}
        sed -i "s/constexpr.*\/\/.*PACKAGE_NAME.*stamp.sh/constexpr char *PACKAGE_NAME = \"${PACKAGE_NAME}\"; \/\/ PACKAGE_NAME set by stamp.sh/g" ${FMPACKAGE_CPP}
        sed -i "s/constexpr.*\/\/.*PACKAGE_EMAIL.*stamp.sh/constexpr char *PACKAGE_EMAIL = \"${PACKAGE_EMAIL}\"; \/\/ PACKAGE_EMAIL set by stamp.sh/g" ${FMPACKAGE_CPP}
        sed -i "s/constexpr.*\/\/.*PACKAGE_URL.*stamp.sh/constexpr char *PACKAGE_URL = \"${PACKAGE_URL}\"; \/\/ PACKAGE_URL set by stamp.sh/g" ${FMPACKAGE_CPP}
        if which indent > /dev/null ; then indent ${FMPACKAGE_CPP} ; fi
        echo "patching ${FMVERSION_CPP} with version major=${VERSION_MAJOR} minor=${VERSION_MINOR} stamp=${VERSION_STAMP}"
        sed -i "s/constexpr.*\/\/.*VERSION_MAJOR.*stamp.sh/constexpr int VERSION_MAJOR = ${VERSION_MAJOR}; \/\/ VERSION_MAJOR set by stamp.sh/g" ${FMVERSION_CPP}
        sed -i "s/constexpr.*\/\/.*VERSION_MINOR.*stamp.sh/constexpr int VERSION_MINOR = ${VERSION_MINOR}; \/\/ VERSION_MINOR set by stamp.sh/g" ${FMVERSION_CPP}
        sed -i "s/constexpr.*\/\/.*VERSION_STAMP.*stamp.sh/constexpr char *VERSION_STAMP = \"${VERSION_STAMP}\"; \/\/ VERSION_STAMP set by stamp.sh/g" ${FMVERSION_CPP}
        if which indent > /dev/null ; then indent ${FMVERSION_CPP} ; fi
        echo "patching ${CONFIGURE_AC} with version ${VERSION_DOT}"
        sed -i "s/^AC_INIT.*/AC_INIT([${PACKAGE_NAME}],[${VERSION_DOT}],[${PACKAGE_EMAIL}],[${PACKAGE_TARNAME}],[${PACKAGE_URL}])/g" ${CONFIGURE_AC}
    fi
}

find_configure_ac
find_fmversion_cpp
find_fmpackage_cpp
git_check
git_changelog
calc_branch
calc_commits
do_patch

