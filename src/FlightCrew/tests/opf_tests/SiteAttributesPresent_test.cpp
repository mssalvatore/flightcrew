/************************************************************************
**
**  Copyright (C) 2010  Strahinja Markovic
**
**  This file is part of FlightCrew.
**
**  FlightCrew is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  FlightCrew is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <stdafx_tests.h>
#include "Validators/Opf/SiteAttributesPresent.h"
#include "Result.h"

using namespace FlightCrew;

TEST( SiteAttributesPresentTest, NotAllowedAttributes )
{
    SiteAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/SiteAttributesPresent_NotAllowedAttributes.xml" );
            
    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_ATTRIBUTE_NOT_RECOGNIZED );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 72 );
    
    std::vector< std::string > message_arguments1 = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments1[ 0 ], "breakme" );
    EXPECT_EQ( message_arguments1[ 1 ], "site" );
}

TEST( SiteAttributesPresentTest, MissingAttributes )
{
    SiteAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/opf_tests/SiteAttributesPresent_MissingAttributes.xml" );

    ASSERT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_REQUIRED_ATTRIBUTE_MISSING );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 31 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "title" );
    EXPECT_EQ( message_arguments[ 1 ], "site" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_XML_REQUIRED_ATTRIBUTE_MISSING );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 31 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "href" );
    EXPECT_EQ( message_arguments[ 1 ], "site" );
}

TEST( SiteAttributesPresentTest, AllowedAttributes )
{
    SiteAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/SiteAttributesPresent_AllowedAttributes.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

