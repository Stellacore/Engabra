#
# Set first argument to string suitable for use in project release branding
#

function(setReleaseTag ReleaseTagVar)

	# return value
	set (ResultString, "FooFooFoo")

	# message("func: ReleaseTagVar = ${ReleaseTagVar}")
	# message("func: \$\{${ReleaseTagVar}\} = '${${ReleaseTagVar}}'")


	if(${ReleaseTagVar})

		# If already set, then use the explicit version passed in
		message("### ReleaseTagVar: Using provided: '${ReleaseTagVar}'")
		#		set(ResultString ${ReleaseTagVar})

	else(${ReleaseTagVar})

		# -- use timestamp
		# string (TIMESTAMP ResultString UTC)

		# -- use git describe info
		if(UNIX)
			set(GIT_CMD "git")
		endif(UNIX)
		if(WIN32)
			set(GIT_CMD "CMD /c git")
		endif(WIN32)

		# run git command to extract tag info
		execute_process(
			COMMAND ${GIT_CMD} describe
			OUTPUT_VARIABLE ResultString
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			OUTPUT_STRIP_TRAILING_WHITESPACE
			)

	endif(${ReleaseTagVar})


	set (${ReleaseTagVar} ${ResultString} PARENT_SCOPE)

endfunction(setReleaseTag)

