# Check if the Dangerfile was changed
has_dangerfile_changes = git.modified_files.include? "Dangerfile"
# Check if the Gemfile was changed
has_gemfile_changes = git.modified_files.include? "Gemfile"
# Check if the license file was changed
has_license_changes = git.modified_files.include? "UNLICENSE"
# Check if the header was changed
has_app_changes = git.modified_files.include? "assertions.h"
# Check if any of the tests were changed
has_test_changes = !git.modified_files.grep(/test/).empty?

# Allow Bitmodo members to bypass some checks
unless github.api.organization_member?('bitmodo', github.pr_author)
    # Fail if the PR does not provide a description
    failure "Please provide a summary in the Pull Request description" if github.pr_body.length < 5

    # Fail if the license was modified by an external user
    failure "The license has been modified" if has_license_changes

    # Warn if the Dangerfile was changed by an external contributor
    warn "#{github.html_link("Dangerfile")} has been modified by external contributor" if has_dangerfile_changes

    # Warn if the Gemfile was changed by an external contributor
    warn "#{github.html_link("Gemfile")} has been modified by external contributor" if has_gemfile_changes

    # Provide a thanks message if the user is external
    message ":+1: Thank you for contributing!"
else
    # Warn if the license has been modified
    warn "The license has been modified" if has_license_changes

    # Provide a message if the user is internal
    message ":ok_hand:"
end

# Warn if the header has changed but the tests have not
warn "Tests have not been updated" if has_app_changes && !has_test_changes

# Create a warning if the PR is a work in progress
warn "PR is classed as Work in Progress" if github.pr_title.include? "[WIP]"
# Warn if the PR is not assigned to anyone
warn "This PR does not have any assignees yet." unless github.pr_json["assignee"]
# Warn if the PR is not mergeable
warn "This PR cannot be merged yet" unless github.pr_json["mergeable"]
